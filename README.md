# Spear

Spear is an fast and efficient full text search engine. 

# Key Features

- Hashmap stored in memory making for very fast text lookups
- Data is periodically stored asyncronously to the disk
- Two very baic commands `ADD` and `GET` which can be accessed over telnet
- Returns a reference to the text in a different location
- Returns JSON array of strings that reference the data in a different location

# Example Usage

#### Index Text

```
$ spear add "Let's go to New York city" 78
```

#### Lookup Text

```
$ spear get "New York"
['78', '533', '7245']
```

The returned values are IDs for lookup in another database. 
