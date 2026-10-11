# Pokémon Field Test Cases

These 17 functional checks are documented in the project PDF. Results marked as confirmed reflect the behavior reported while running the game; screenshot references point to `Screenshots/` and the PDF appendices.

| # | Action | Expected result | Documented result |
|---:|---|---|---|
| 1 | Press Enter on the opening screen | Professor dialogue appears | Passed; Figures 1–2 |
| 2 | Advance dialogue to player-name entry | Player-name prompt appears | Passed; Figures 3–4 |
| 3 | Press Enter with the player-name field empty | Remain at name entry | Passed; confirmed during play |
| 4 | Enter a player name and press Enter | Name is accepted and dialogue continues | Passed; ANDI confirmed in Figure 5 |
| 5 | Press Enter with the rival-name field empty | Remain at rival-name entry | Passed; confirmed during play, Figure 6 shows the empty field |
| 6 | Enter a rival name and press Enter | Name is accepted and dialogue continues | Passed; Berry confirmed in Figures 7–8 |
| 7 | Move with W, A, S, D in the laboratory | Player moves in the corresponding directions | Passed; Figures 9–11 |
| 8 | Move into a shelf or table | Player is blocked by the furniture | Passed; confirmed during play, Figure 12 |
| 9 | Try to leave the first lab without choosing a Poké Ball | Remain in the first laboratory | Passed; confirmed during play |
| 10 | Click a Poké Ball and choose a starter | Starter screen opens and each starter choice registers | Passed; all three confirmed, Figures 13 and 26 |
| 11 | Reach the second-lab exit | Rival event appears | Passed; Figure 15 |
| 12 | Press Enter in the rival event | Match starts at 0–0 | Passed; Figure 16 |
| 13 | Move into and kick the ball | Ball responds; goals update when it enters a goal | Passed; Figures 17–19 and 22–23 |
| 14 | Score three goals as the player | Victory state appears | Passed; Figure 20 |
| 15 | Allow Arceus to score three goals, then press Enter | Defeat state appears and Enter exits | Passed; Figure 24 and confirmed during play |
| 16 | Press R in the defeat state | Match restarts with scores and positions reset | Passed; Figure 25 and confirmed during play |
| 17 | Continue after victory and use the closing controls | Closing screen appears; Enter or Escape exits | Passed; closing screen shown in Figure 21; final exit action was not captured |

The full test descriptions and screenshots are in `Pokemon_Field_Project_Documentation.pdf`.
