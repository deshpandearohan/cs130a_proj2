import matplotlib.pyplot as plt
import pandas as pd
import sys

def plot_hashes(filename, title):
    # Load the CSV file (no header)
    df = pd.read_csv(filename, header=None)

    # Each row is: h1, h2
    x = range(len(df))            # input index (0, 1, 2, 3...)
    h1 = df[0]
    h2 = df[1]

    plt.figure(figsize=(10, 6))
    plt.scatter(x, h1, s=4, alpha=0.5, label="h1")
    plt.scatter(x, h2, s=4, alpha=0.5, label="h2")

    plt.title(title)
    plt.xlabel("Input index")
    plt.ylabel("Hash output (0..m-1)")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()


def main():
    if len(sys.argv) != 2:
        print("Usage: python plot_hashes.py <resultsX.csv>")
        return

    filename = sys.argv[1]
    title = f"Scatter Plot of {filename}"
    plot_hashes(filename, title)


if __name__ == "__main__":
    main()