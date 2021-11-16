'''
test_dictionary.py

This module "tests" a dictionary of words and definitions.
There there can be multiple definitions for a word.

Created on May 23, 2019

@author: philip gust
'''
import dictionary

# put entries including one with duplicate word
dictionary.putDictionaryEntry("name1", "value1")
dictionary.putDictionaryEntry("name2", "value2.1")
dictionary.putDictionaryEntry("name2", "value2.2")
dictionary.putDictionaryEntry("name3", "value3")

# get first entry for "name2"
word = "name2"
entry_no = dictionary.getDictionaryEntry(word);
print("word: ", word, "entry_no: ", entry_no)
if entry_no >= 0:
    word_def = dictionary.getDictionaryDefinition(entry_no)
    print("word: ", word, "definition: ", word_def)

# get second entry for "name2"
word = "name2*"
entry_no = dictionary.getDictionaryEntry(word, entry_no+1)
print("word: ", word, "entry_no: ", entry_no)
if entry_no >= 0:
    word_def = dictionary.getDictionaryDefinition(entry_no)
    print("word: ", word, "definition: ", word_def)

# get non-existant third entry for "name2"
word = "name2"
entry_no = dictionary.getDictionaryEntry(word, entry_no+1)
print("word: ", word, "entry_no: ", entry_no)
if entry_no >= 0:
    word_def = dictionary.getDictionaryDefinition(entry_no)
    print("word: ", word, "definition: ", word_def)
