from flask import Flask, render_template, request

app = Flask(__name__)  #turn this line into a flask app

@app.route("/", methods=["GET", "POST"])  # the code should execute when the user visits / of the site(index)
def index():
    if request.method == "GET":
        return render_template("index.html")
    elif request.method == "POST":
        return render_template("greet.html", name=request.form.get("name", "world"))