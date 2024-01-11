import os
import logging
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Password hash variable
logger = logging.getLogger("werkzeug")

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session.get("user_id")
    stocks_owned = db.execute(
        "SELECT DISTINCT symbol FROM records WHERE buyer_id = ?", user_id
    )

    symbol_list = []
    shares_list = []
    symbol_price_list = []
    total_value_list = []
    cash_balance_unf = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash_balance = cash_balance_unf[0]["cash"]

    # print(cash_balance[0]['cash'])

    if request.method == "GET":
        # print("STOCKS OWNED: ",stocks_owned)
        # print("stocks1: ", row)

        for i in stocks_owned:
            query = db.execute(
                "SELECT SUM(shares) FROM records WHERE symbol = ?;", i["symbol"]
            )
            symbol_list.append(i["symbol"])
            shares_list.append(query[0]["SUM(shares)"])

        for s in symbol_list:
            symbol_info = lookup(s)
            symbol_price = symbol_info.get("price")
            symbol_price_list.append(symbol_price)
        # print(symbol_price_list)

        for t in range(len(symbol_price_list)):
            total_value = symbol_price_list[t] * shares_list[t]
            total_value_list.append(total_value)

        total_value_stock = sum(total_value_list)
        print("CASH BALANCE: ", cash_balance)
        print("TOTAL VALUE STOCK: ", total_value_stock)
        grand_total = cash_balance + total_value_stock
        print("GRAND TOTAL: ", grand_total)

        return render_template(
            "index.html",
            symbols=symbol_list,
            shares=shares_list,
            prices=symbol_price_list,
            total_values=total_value_list,
            cash_balance=usd(cash_balance),
            grand_total=usd(grand_total),
        )
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    buyer_id = session.get("user_id")
    # Method GET
    if request.method == "GET":
        return render_template("buy.html")

    # Method POST
    elif request.method == "POST":
        # Request symbol
        symbol = request.form.get("symbol")
        # Request shares
        shares = request.form.get("shares")

        # Check if the input shares is a number
        if shares.isnumeric():
            # Turn shares into an integer
            shares = int(shares)
            # Ceck if shares is a positive Number
            if shares < 1:
                return apology("You must enter a positive Number", 400)

        # If shares input is not a number
        elif not shares.isnumeric():
            return apology("You must Enter a Number", 400)

        symbol_info = lookup(symbol)
        if symbol_info is None:
            return apology("please enter valid stock")
        stock_price = symbol_info.get("price")
        current_date = datetime.datetime.now()
        transaction_type = "BUY"

        rows = db.execute("SELECT cash from users WHERE id = ?", buyer_id)
        current_cash = rows[0]["cash"]

        if symbol_info is not None and shares > 0:
            if current_cash >= (stock_price * shares):
                db.execute(
                    "INSERT INTO records (buyer_id, transaction_type, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?, ?)",
                    buyer_id,
                    transaction_type,
                    symbol,
                    shares,
                    stock_price,
                    current_date,
                )
                db.execute(
                    "UPDATE users SET cash = ? WHERE id = ?",
                    current_cash - (stock_price * shares),
                    buyer_id,
                )

                return redirect("/")
            else:
                return apology("No enough cash")
        elif symbol_info is None:
            return apology("Please enter a symbol")
    return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session.get("user_id")
    user_records = db.execute("SELECT * FROM records WHERE buyer_id = ?", user_id)

    transaction_type_list = []
    symbol_list = []
    shares_list = []
    price_list = []
    date_list = []

    if request.method == "GET":
        for i in user_records:
            transaction_type_list.append(i["transaction_type"])
            symbol_list.append(i["symbol"])
            shares_list.append(i["shares"])
            price_list.append(i["price"])
            date_list.append(i["date"])

        return render_template(
            "history.html",
            transactions=transaction_type_list,
            symbols=symbol_list,
            shares=shares_list,
            prices=price_list,
            dates=date_list,
        )

    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # if GET
    if request.method == "GET":
        return render_template("quote.html")

    # if POST
    if request.method == "POST":
        requested_symbol = request.form.get("symbol")

        symbol_info = lookup(requested_symbol)
        if symbol_info is not None:
            name = symbol_info["name"]
            price = symbol_info["price"]
            symbol = symbol_info["symbol"]

            return render_template("quoted.html", name=name, price=price, symbol=symbol)
        else:
            name = "does not exist"
            return apology("Symbol does not exist", 400)
            # return render_template("quoted.html", name=name)
    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    names_in_db = db.execute("SELECT username FROM users")

    # Forget any user_id
    session.clear()

    # Ensure POST Method
    if request.method == "POST":
        # Ensure username submit
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password submit
        elif not request.form.get("password"):
            return apology("must enter password to register", 400)
        # Ensure password confirmation
        elif not request.form.get("confirmation"):
            return apology("must enter password confirmation to register", 400)

        # Ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords must match", 400)

        else:
            username = request.form.get("username")
            password = request.form.get("password")
            confirmpassword = request.form.get("confirmation")

            print(names_in_db)

            for n in names_in_db:
                print(n["username"])
                if n["username"] == username:
                    return apology("User already registered!", 400)

            hash = generate_password_hash(password, method="pbkdf2", salt_length=16)
            # to check hash (werkzeug.security.check_password_hash(pwhash, password))

            db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)", username, hash
            )

        # redirect to login page
        return redirect("/login")

    # if reached route via GET
    else:
        return render_template("register.html")

    # return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User ID
    buyer_id = session.get("user_id")

    # Check which stocks the user owns
    owned_stock = db.execute(
        "SELECT DISTINCT symbol, SUM(shares) FROM records WHERE buyer_id = ? GROUP BY symbol",
        buyer_id,
    )

    # CONVERT LIST TO DICTIONARY
    owned_stock_simple = {
        item["symbol"]: str(item["SUM(shares)"]) for item in owned_stock
    }

    selected_stock = None

    # Method POST
    if request.method == "POST":
        # Get Symbol from Select Menu
        stock_to_sell = request.form.get("symbol")

        # Gets Value from selected Key (symbol) / Shares from selected stock
        selected_stock_owned_shares = owned_stock_simple.get(stock_to_sell)

        # Convert owned shares shares to Int
        if selected_stock_owned_shares is not None:
            selected_stock_owned_shares = int(selected_stock_owned_shares)
        else:
            return apology("No Stock Selected", 403)

        # Get the # of shares to sell from selected stock
        shares_to_sell = request.form.get("shares")

        # Convert input to int
        if len(shares_to_sell) != 0:
            # Check that shares to sell is a number and positive
            if shares_to_sell.isnumeric() and int(shares_to_sell) > 0:
                shares_to_sell = int(shares_to_sell)
            else:
                return apology("Incorrect Input", 400)
        else:
            return apology("You left input empty", 403)

        # Check if user has enough shares to sale
        if selected_stock_owned_shares is not None:
            if selected_stock_owned_shares < shares_to_sell:
                return apology("Not enough shares", 400)
            else:
                transaction_type = "SELL"
                symbol = stock_to_sell
                shares = shares_to_sell
                symbol_info = lookup(symbol)
                stock_price = symbol_info.get("price")
                current_date = datetime.datetime.now()

                rows = db.execute("SELECT cash from users WHERE id = ?", buyer_id)
                current_cash = rows[0]["cash"]

                db.execute(
                    "INSERT INTO records (buyer_id, transaction_type, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?, ?)",
                    buyer_id,
                    transaction_type,
                    symbol,
                    -shares,
                    stock_price,
                    current_date,
                )
                db.execute(
                    "UPDATE users SET cash = ? WHERE id = ?",
                    current_cash + (stock_price * shares),
                    buyer_id,
                )

                return redirect("/")

        # DEBUG

        print("STOCK TO SELL:")
        print(stock_to_sell)
        print(type(stock_to_sell))
        print("SELECTED STOCK OWNED SHARES:")
        print(selected_stock_owned_shares)
        print(type(selected_stock_owned_shares))
        print("SHARES TO SELL:")
        print(shares_to_sell)
        print(type(shares_to_sell))

        return render_template("sell.html", owned=owned_stock_simple)

    # Method GET
    else:
        print(owned_stock)
        print(owned_stock_simple)

        return render_template("sell.html", owned=owned_stock_simple)

    # PERSONAL TOUCH
    # ADD CASH


@app.route("/add_cash", methods=["GET", "POST"])
def add_cash():
    # User ID
    user_id = session.get("user_id")

    if request.method == "POST":
        add_cash = request.form.get("add_cash")

        if add_cash.isnumeric():
            add_cash = int(add_cash)
            if add_cash < 1:
                return apology("you must enter a positive number", 400)
            else:
                rows = db.execute("SELECT cash from users WHERE id = ?", user_id)
                current_cash = rows[0]["cash"]

                db.execute(
                    "UPDATE users SET cash = ? WHERE id = ?",
                    current_cash + (add_cash),
                    user_id,
                )
                flash("{} Cash added to your account".format(add_cash), "success")
                return redirect("/")
        else:
            return apology("You must enter a valid Input", 400)

    return apology("TO DO")


if __name__ == "__main__":
    app.run(debug=True)
