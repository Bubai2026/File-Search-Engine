from flask import Flask, request, jsonify, render_template
import subprocess
import os

app = Flask(__name__)

SEARCH_PROGRAM = os.path.join(
    os.path.dirname(__file__),
    "search"
)

DOCUMENTS = os.path.join(
    os.path.dirname(__file__),
    "data",
    "documents"
)


@app.route("/")
def home():
    return render_template("index.html")


@app.route("/search")
def search():
    query = request.args.get("q", "").strip()

    if not query:
        return jsonify([])

    try:
        result = subprocess.run(
            [SEARCH_PROGRAM, DOCUMENTS, query],
            capture_output=True,
            text=True,
            timeout=10
        )
    except Exception as e:
        return jsonify({"error": str(e)}), 500

    if result.returncode != 0:
        return jsonify({
            "error": result.stderr.strip() or "Search failed"
        }), 500

    results = []

    for line in result.stdout.splitlines():
        parts = line.split("\t")

        if len(parts) != 2:
            continue

        results.append({
            "file": parts[0],
            "score": float(parts[1])
        })

    return jsonify(results)


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
