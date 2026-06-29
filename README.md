## Exp Rate Tuner
This allows you to lower (or disable) kill-based experience on a character.

## Requirements
Requires an AzerothCore server

## Installation
```
1. Simply place the module under the `modules` directory of your AzerothCore source. 
2. Re-run cmake and launch a clean build of AzerothCore.
```

The experience rate is stored per-character in `acore_characters.mod_exp_rate_tuner_character_settings`
and defaults to 100% (normal experience). The row is removed automatically when the character is deleted.

### In-Game Commands
The module adds the following in-game command:

| Command | Description |
|----------|--------------|
| `.exprate set <0-100>` | Sets the current character's kill experience rate as a percentage (0 = no experience, 100 = normal experience) of the experience earned from killing monsters. Quest, exploration, and battleground experience are not affected. |