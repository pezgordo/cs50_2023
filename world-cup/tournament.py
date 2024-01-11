# Simulate a sports tournament

import csv
import sys
import random

from sys import argv

# Number of simluations to run
N = 1000


def main():
    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    with open(argv[1], newline="") as teams_file:
        file_reader = csv.DictReader(teams_file, fieldnames=["team", "rating"])
        next(file_reader, None)
        for row in file_reader:
            row["rating"] = int(row["rating"])

            teams.append(row)

    counts = {}

    for i in range(len(teams)):
        team_add = {(list(teams[i].values())[0]): 0}
        counts.update(team_add)

    # TODO: Simulate N tournaments and keep track of win counts
    test_start = 0
    while test_start != N:
        counts[simulate_tournament(teams)] += 1

        test_start = test_start + 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    winner = []
    winners = []
    win = False

    for t in teams:
        winners.append(t)

    i = len(winners)

    while len(winners) != 2:
        winners = simulate_round(winners)

        i = i / 2

    if i == 2:
        win = simulate_game(winners[0], winners[0 + 1])

        if win == True:
            winner.append(winners[0])

        elif win == False:
            winner.append(winners[0 + 1])

    return list(winner[0].values())[0]


if __name__ == "__main__":
    main()
