greeting = input("Greeting: ")
greeting = greeting.lower()

if greeting.startswith("hello"):
    print("$0")
elif greeting[0] == "h":
    print("$20")
else:
    print("$100")
