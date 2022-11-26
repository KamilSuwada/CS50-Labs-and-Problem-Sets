# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # open file
    with open(sys.argv[1], "r") as f:
        # create dict reader
        reader = csv.DictReader(f)
        # iterate rows in csv
        for row in reader:
            # create team
            team = {
                "team": row["team"],
                "rating": int(row["rating"])
            }
            # add team
            teams.append(team)

    counts = {}

    # simulate N tournaments
    for _ in range(N):
        # get the winner
        winner = simulate_tournament(teams)

        # log the winner
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1

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
    # get round winners
    winners = simulate_round(teams)
    # repeat rounds until there is only one winner in winners list
    while len(winners) != 1:
        winners = simulate_round(winners)

    # return the winner's name
    return winners[0]["team"]


if __name__ == "__main__":
    main()
