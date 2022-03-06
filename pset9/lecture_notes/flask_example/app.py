from flask import Flask, render_template, request

# Turns this file into a Flask application
app = Flask(__name__)

# Defines a route for default page
@app.route("/")

# Render or print html file to user screen
def index():
    # Requests commaand line arguemnts
    name = request.args.get("name")
    return render_template("index.html", name=name)

# Defines a route for the greet page
@app.route("/greet", methods=["POST"])
def greet():
    name = request.form.get("name", "world")
    return render_template("greet.html", name=name)