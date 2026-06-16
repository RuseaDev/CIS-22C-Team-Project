# Polynomial Rolling Hash

## Formula

The hash table scans each key from left to right while maintaining a running
hash value:

```text
h = 0
for each character c in key:
    h = (h * BASE + ascii(c)) % tableSize
```

Expanding the loop shows the underlying polynomial:

```text
hash(key) = ( ascii(key[0]) * BASE^(n-1)
           +  ascii(key[1]) * BASE^(n-2)
           +  ...
           +  ascii(key[n-1]) * BASE^0 ) % tableSize
```

Each character gets a positional weight, so rearranging characters changes the
hash. For example, `DL303` and `LD303` do not hash the same way they would with
a simple character-sum hash.

## Why Base 31

The implementation uses `BASE = 31` because:

- It is prime, which helps reduce repeated mappings compared with a composite
  base.
- It is small, so `h * 31 + c` stays manageable before the modulo step.
- It is a common base for alphanumeric string hashing.

## Why Not Simple Modulo Division

The project requirement forbids converting the key to a number and using simple
modulo division. This would be a poor fit for mixed flight-number strings:

```text
BAD: h = stoi("003") % tableSize -> h = 3 % 53 = 3
```

That approach throws away character-position information, so keys such as `003`
and `300` could hash identically. Polynomial rolling hash uses every character
at its position, so it satisfies the requirement.

## Worked Example

For key `DL303`, table size `11`, and base `31`:

```text
char | ASCII | h = (h * 31 + ASCII) % 11
-----|-------|----------------------------------
'D'  |  68   | (0 * 31 + 68) % 11 = 68 % 11 = 2
'L'  |  76   | (2 * 31 + 76) % 11 = 138 % 11 = 6
'3'  |  51   | (6 * 31 + 51) % 11 = 237 % 11 = 6
'0'  |  48   | (6 * 31 + 48) % 11 = 234 % 11 = 3
'3'  |  51   | (3 * 31 + 51) % 11 = 144 % 11 = 1
```

The final hash index is `1`.

## Known Limitation

Flight numbers such as `AA101` and `DL303` include both letters and digits, so
the polynomial hash is a better fit than reducing the key to a numeric ID.
However, it can still produce collisions. The hash table handles collisions with
linear probing and tracks collision statistics separately.
