import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    user = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"])
    portfolio = db.execute("SELECT company, SUM(shares) FROM trades WHERE trader_id = :id GROUP BY company HAVING SUM(shares) > 0 ", id = session["user_id"])
    n = len(portfolio)
    cash = round(user[0]['cash'], 2)
    temp = []
    for row in range(n):
        temp.append(portfolio[row]['company'])
    companies = []
    for x in range(n):
        companies.append(lookup(temp[x]))
    total = 0
    for y in range(n):
        value = (portfolio[y]['SUM(shares)'] * companies[y]['price'])
        total += value
    return render_template("index.html", user=user, portfolio=portfolio, companies=companies, n=n, total=total, cash=cash)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        funds = db.execute("SELECT cash FROM users WHERE id = :id",
                                   id = session["user_id"])
        cash = round(funds[0]['cash'], 2)
        return render_template("buy.html", cash=cash)
    else:
        share = lookup(request.form.get("symbol"))
        number = int(request.form.get("shares"))

        if share == None:
            return apology("Invalid symbol", 403)
        elif number <= 0:
            return apology("Invalid number of shares", 403)
        else:
            funds = db.execute("SELECT cash FROM users WHERE id = :id",
                                   id = session["user_id"])
            if share['price'] * number > funds[0]['cash']:
                return apology("Insufficient funds", 403)

            else:
                db.execute("INSERT INTO trades (trader_id, company, shares, price, time) VALUES (:trader_id, :company, :shares, :price, datetime())",
                            trader_id=session["user_id"], company = share['symbol'], shares = number, price = share['price'])
                db.execute("UPDATE users SET cash = :balance WHERE id = :id",
                            balance = funds[0]['cash'] - (share['price'] * number), id = session["user_id"])
                return redirect("/")





@app.route("/history")
@login_required
def history():
    user = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"])
    history = db.execute("SELECT * FROM trades WHERE trader_id = :id ORDER BY time DESC", id = session["user_id"])
    n = len(history)

    return render_template("history.html", user=user, history=history, n=n)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    if request.method=="GET":
        return render_template("quote.html")
    else:
        symbol = lookup(request.form.get("symbol"))

        if symbol == None:
            return apology("Invalid symbol", 403)
        else:
            return render_template("quoted.html", symbol=symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method=="GET":
        return render_template("register.html")
    else:
        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        elif not request.form.get("confirm_password"):
            return apology("must confirm password", 403)

        elif request.form.get("password") != request.form.get("confirm_password"):
            return apology("Passwords do not match", 403)

        else:
            check_user = db.execute("SELECT * FROM users WHERE username = :username",
                                    username = request.form.get("username"))
            if len(check_user) != 0:
                return apology("username already exists", 403)

            else:
                username = request.form.get("username")
                password = request.form.get("password")

                db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                            username=username, hash=generate_password_hash(password))
                return redirect("/")



    return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        portfolio = db.execute("SELECT company, SUM(shares) FROM trades WHERE trader_id = :id GROUP BY company HAVING SUM(shares) > 0", id = session["user_id"])
        n = len(portfolio)
        return render_template("sell.html", portfolio=portfolio, n=n)
    else:
        funds = db.execute("SELECT cash FROM users WHERE id = :id",
                                   id = session["user_id"])
        share = lookup(request.form.get("symbol"))
        number = int(request.form.get("shares"))
        owned = db.execute("SELECT SUM(shares) FROM trades WHERE trader_id = :id AND company = :company GROUP BY company ",
                            id = session["user_id"], company = share['symbol'])

        if number <= 0 or number > owned[0]['SUM(shares)']:
            return apology("You can't sell that many shares", 403)


        else:
            db.execute("INSERT INTO trades (trader_id, company, shares, price, time) VALUES (:trader_id, :company, :shares, :price, datetime())",
                        trader_id=session["user_id"], company = share['symbol'], shares = -number, price = share['price'])
            db.execute("UPDATE users SET cash = :balance WHERE id = :id",
                        balance = funds[0]['cash'] + (share['price'] * number), id = session["user_id"])
            return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
