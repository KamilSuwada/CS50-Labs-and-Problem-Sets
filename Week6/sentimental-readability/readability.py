import cs50


# Get text
text = cs50.get_string("Text: ")

# Compute number of letters
number_of_letters = len([i for i in [*text] if i.isalpha()])

# Compute number of words
number_of_words = len(text.split(" "))

# Compute number of sentences
number_of_sentences = len([i for i in [*text] if i == "." or i == "!" or i == "?"])

# Compute the index
L = 100.0 * float(number_of_letters) / float(number_of_words)
S = 100.0 * float(number_of_sentences) / float(number_of_words)
index = (0.0588 * L) - (0.296 * S) - 15.8
i = round(index)

# Classify the index to grades
if i > 16:
    print("Grade 16+")
elif i < 1:
    print("Before Grade 1")
else:
    print(f"Grade {i}")