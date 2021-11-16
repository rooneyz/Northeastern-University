'''
dictionary.py

This module implements a dictionary of words and definitions.
There there can be multiple definitions for a word. This
implementation uses data classes for the _DictionaryEntry
and _Dictionary types

Created on May 23, 2019

@author: philip gust
'''

'''
Dictionary entry with word and definition
'''
class _DictionaryEntry:
    word: str = None
    definition: str = None

'''
Dictionary with array of _Dictionary entries
'''
class _Dictionary:
    entries: list = []  # empty list of dictionary entries

'''
The dictionary
'''
_dict = _Dictionary()

'''
Return the number of entries in the dictionary

@return number of entries in the dictionary
'''
def getDictionarySize():
    return len(_dict.entries)

''' 
Get dictionary word.

@param entry_no the index of the entry
@return word if entry found else None
'''
def getDictionaryWord(entry_no):
    if entry_no >= 0 and entry_no < len(_dict.entries):
        return _dict.entries[entry_no].word

''' 
Get dictionary definition.

@param entry_no the index of the entry
@return definition if entry found else None
'''
def getDictionaryDefinition(entry_no):
    if entry_no >= 0 and entry_no < len(_dict.entries):
        return _dict.entries[entry_no].definition


''' 
Find dictionary entry for a word. If word ends
with wildcard (*), finds any matching word.

@param word the word to match
@param entry_no the starting entry number
@return entry index or -1 if not found
'''
def getDictionaryEntry(word, entry_no = 0):
    for i in range(entry_no, len(_dict.entries)):
        if word[-1] == "*": # wildcard match
            if _dict.entries[i].word.startswith(word[0:-1]):
                return i
        elif _dict.entries[i].word == word: # regular match
            return i
    return -1

'''
Put dictionary definition entry for word.
@param word the entry word
@param def the entry definition
@return index of new entry
'''
def putDictionaryEntry(word, definition):
    entry = _DictionaryEntry()
    entry.word = word;
    entry.definition = definition
    _dict.entries.append(entry)
    return len(_dict.entries)-1
