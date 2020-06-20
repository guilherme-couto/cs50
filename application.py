import os

from cs50 import SQL
from flask import g, Flask, flash, jsonify, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import login_required, apology

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

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///maaqui.db")


@app.route("/")
def index():
    """Info sobre site"""

    return render_template("index.html")


@app.route("/quadro")
@login_required
def quadro():
    """Página inicial do user"""

    pedidos = db.execute("SELECT * FROM pedidos WHERE ajudado = 0 ORDER BY valid")

    return render_template("quadro.html", pedidos=pedidos)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Query database for cpf
        rows = db.execute("SELECT * FROM users WHERE cpf = :cpf",
                          cpf=request.form.get("cpf"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("senha")):
            return render_template("login.html", mensagem="Usuário ou senha incorretos")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/quadro")

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


@app.route("/registrar", methods=["GET", "POST"])
def registrar():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure confirmation matches password
        if request.form.get("senha") != request.form.get("confirmation"):
            return render_template("registrar.html", mensagem="A senhas não conferem")

        # Query database for cpf
        rows = db.execute("SELECT * FROM users WHERE cpf = :cpf",
                          cpf=request.form.get("cpf"))

        # Ensure cpf is in use
        if len(rows) != 0:
            return render_template("registrar.html", mensagem="CPF já cadastrado")

        # Register user in users
        db.execute("INSERT INTO users (nome, cpf, cel, email, hash) VALUES (:nome, :cpf, :cel, :email, :hash)",
                    nome=str.capitalize(request.form.get("nome")), cpf=request.form.get("cpf"),
                    cel=request.form.get("cel"), email=request.form.get("email"),
                    hash=generate_password_hash(request.form.get("senha")))

        # Remember which user has logged in
        session["user_id"] = db.execute("SELECT id FROM users WHERE cpf = :cpf",
                                        cpf=request.form.get("cpf"))

        # Redirect user to home page
        return redirect("/quadro")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("registrar.html")


@app.route("/novo", methods=["GET", "POST"])
@login_required
def novo():
    """Add project"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Update pedidos
        db.execute("INSERT INTO pedidos (user_id, descri, titulo, valor, valid) VALUES (:user_id, :descri, :titulo, :valor, :valid)",
                    user_id=session["user_id"], descri=request.form.get("descricao"), titulo=request.form.get("titulo"),
                    valor=request.form.get("valor"), valid=request.form.get("validade"))

        # Redirect user to home page
        return redirect("/quadro")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("novo.html")


@app.route("/ajudar", methods=["GET", "POST"])
@login_required
def ajudar():
    """Ajudar pedido"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure pedido exists
        rows = db.execute("SELECT num FROM pedidos WHERE num = :numero", numero=int(request.form.get("numero")))

        if len(rows) != 1:
            return render_template("novo.html", mensagem="Número do pedido não confere")

        # Render new template with pedido infos
        user = db.execute("SELECT nome, cel, email FROM users WHERE id IN (SELECT user_id FROM pedidos WHERE num = :numero)",
                            numero=int(request.form.get("numero")))

        pedido = db.execute("SELECT * FROM pedidos WHERE num = :numero", numero=request.form.get("numero"))

        # Update pedido para ajudado
        db.execute("UPDATE pedidos SET ajudado = 1 WHERE num = :numero", numero=request.form.get("numero"))

        return render_template("ajudado.html", pedido=pedido, user=user)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("ajudar.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)