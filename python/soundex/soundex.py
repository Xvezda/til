#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import re
import logging

logger = logging.getLogger(__name__)
logger.addHandler(logging.StreamHandler())


def soundex(text):
    """
    [Soundex on Wikipedia](https://en.wikipedia.org/wiki/Soundex)

    > The correct value can be found as follows:
    >
    > 1. Retain the first letter of the name and drop all other occurrences of
    >    a, e, i, o, u, y, h, w.
    > 2. Replace consonants with digits as follows (after the first letter):
    >    b, f, p, v → 1
    >    c, g, j, k, q, s, x, z → 2
    >    d, t → 3
    >    l → 4
    >    m, n → 5
    >    r → 6
    > 3. If two or more letters with the same number are adjacent in the original name
    >    (before step 1), only retain the first letter;
    >    also two letters with the same number separated by 'h' or 'w' are coded as a single number,
    >    whereas such letters separated by a vowel are coded twice.
    >    This rule also applies to the first letter.
    > 4. If you have too few letters in your word that you can't assign three numbers,
    >    append with zeros until there are three numbers.
    >    If you have four or more numbers, retain only the first three.
    """
    # Step 1
    first_letter = text[:1]

    # occurrences = ['a', 'e', 'i', 'o', 'u', 'y', 'h', 'w']
    # remain_text = ''

    # for letter in text[1:]:
    #     if letter in occurrences:
    #         continue  # Drop
    #     remain_text += letter

    occurrences = ['a', 'e', 'i', 'o', 'u', 'y']
    remain_text = text[1:].lower()
    for occurrence in occurrences:
        remain_text = remain_text.replace(occurrence, '0')
    logger.info('Step 1: %s' % remain_text)

    # Step 2
    mapping = [
        None,
        ['b', 'f', 'p', 'v'],
        ['c', 'g', 'j', 'k', 'q', 's', 'x', 'z'],
        ['d', 't'],
        ['l'],
        ['m', 'n'],
        ['r']
    ]

    def number_of(letter):
        for idx, seq in enumerate(mapping):
            if not seq:
                continue
            if letter.lower() in seq:
                return str(idx)
        # raise Exception('"%s" not found' % char)
        return letter

    mapped = remain_text
    for letter in remain_text:
        mapped = mapped.replace(letter, number_of(letter))
    logger.info('Step 2: %s' % mapped)

    # Step 3
    if number_of(first_letter) == number_of(mapped[:1]):
        mapped = mapped[1:]

    mapped = re.sub(r'([1-6])\1+', r'\1', mapped)
    logger.info('Step 3-1: %s' % mapped)

    mapped = re.sub(r'([1-6])[hw]\1', r'\1', mapped)
    logger.info('Step 3-2: %s' % mapped)
    mapped = mapped.replace('0', '')

    result = mapped[:3].ljust(3, '0')
    return first_letter + result

# TODO: Also add implementation of SQL soundex


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--test', '-t', action='store_true')
    parser.add_argument('--verbose', '-v', action='count', default=0)
    parser.add_argument('text', type=str, nargs='?')

    args = parser.parse_args()

    if args.verbose == 1:
        logger.setLevel(logging.INFO)
    elif args.verbose == 2:
        logger.setLevel(logging.DEBUG)

    if args.test:
        assert soundex('Robert') == 'R163'
        assert soundex('Robert') == soundex('Rupert')

        assert soundex('Rubin') == soundex('R150')

        assert soundex('Ashcraft') == 'A261'
        assert soundex('Ashcraft') == soundex('Ashcroft')

        assert soundex('Tymczak') == 'T522'

        assert soundex('Pfister') == 'P236'

        assert soundex('Honeyman') == 'H555'

        print('All test passed')
        parser.exit()

    if args.text:
        print(soundex(args.text))

