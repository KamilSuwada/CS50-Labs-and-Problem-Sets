import sys
import csv


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    database = []

    # open file and read database
    with open(sys.argv[1], "r") as f:
        # create the csv dict reader
        reader = csv.DictReader(f)
        # go through rows:
        for row in reader:
            # initiate person
            person = {}
            # iterate through properties
            for (key, value) in row.items():
                try:
                    # if value can be int, it is the STR repeats
                    person[key] = int(value)
                except:
                    # if not, that filed was persons name: keep as string
                    person[key] = value
            # add person to database
            database.append(person)

    # TODO: Read DNA sequence file into a variable
    sequence = {}
    with open(sys.argv[2], "r") as f:
        sequence["sequence"] = f.readline().strip()

    # TODO: Find longest match of each STR in DNA sequence
    # make sure database has at least one person
    if len(database) > 0:
        # access first person (since all have the same STR data) and iterate through STRs
        for (key, value) in database[0].items():
            # person also has a name so if value is int, then we have accessed STR
            if type(value) != int:
                continue
            # create fields under the STR as str with value of longest match for that STR as int, cast just to make triple sure.
            sequence[key] = int(longest_match(sequence["sequence"], key))
    else:
        print("EMPTY DATABASE!")
        sys.exit(2)

    # TODO: Check database for matching profiles

    # create matches dictionary with false values for all STRs
    matches = {}
    if len(database) > 0:
        for person in database:
            matches[person["name"]] = {}
            for (key, value) in person.items():
                if type(value) != int:
                    continue
                matches[person["name"]][key] = False

    # check every person against all STRs
    for person in database:
        for (key, value) in person.items():
            # try because we also have a "name" key which will fail this check, so we just continue
            try:
                # if STR count matches person, flip false to true.
                if sequence[key] == person[key]:
                    matches[person["name"]][key] = True
            except:
                continue

    # find full match
    for (key, value) in matches.items():
        # check if false is in array made of all matches for a person for all STRs:
        if False not in [val for (k, val) in value.items()]:
            print(key)
            sys.exit(0)

    # if match is not found
    print("No match")
    sys.exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()