# BLACKJACK

## Game Rules
- Each card has a numerical value.
  ○ Numbered cards are counted at their face value (two counts as 2 points, three, 3 points, and so on)
  ○ An Ace count as either 1 point or 11 points (whichever suits the player best)
  ○ Jack, queen and king count 10 points each
- The player will compete against the computer which represents the casino.
- The goal of the player is to try to reach a total point sum of 21 without exceeding it. Whoever exceeds 21 first loses (technically known as busting).
- At the beginning of each round, the player is dealt two open cards and the computer is dealt one open card. The cards are open, meaning that the values are known for both, the player and the computer (no hidden cards).
- The player will see the sum of the points from his 2 open cards and decides whether or not to draw an additional card.
- The player may draw one additional card at a time for as long as he likes or until he busts (sum of drawn cards exceeds 21). If he busts, he loses the round.
- When the player decides that he won’t draw anymore and he is happy with whatever total amount he got, the computer will draw and open an additional card.
- The computer will keep on drawing additional cards, one at a time as long as the sum of its cards is less or equal 16.
- If the computer busts, the player wins.
- If the computer doesn’t bust (total sum is less or equal 21), then the total values are compared between the computer and the player. Whomever has a higher value wins the round.
- If the two totals are the same, no one wins the round (technically called a push).
