# Directive Invasion

## Elevator Pitch
You’ve been assigned by high command to defend the base at all cost from
invading alien space ships. Equipped with a set of gun turrets, you must
destroy the waves of incoming aliens and save humanity.

## Design

### Aliens
The game starts with five rows of ten aliens placed at the top left of the
screen.  The aliens are slowly moving from left to right and when they reach
the right side, they switch direction. Likewise as they reach the left edge.
Each time the aliens reach the side of the screen, they also move down a little
bit.

If the aliens manage to travel all the way down to the player's turret, the
game ends, even if the player has additional turrets left.

If an alien does not have another alien below it, it will occasionally drop
a bomb. The bomb will fall down towards the bottom of the screen and if it hits
the player, the player loses one life.

When all the player's lives are lost, the game ends.

Alien bombs don't collide with other aliens.

### Player
The player in control of a gun turret at the bottom of the screen. The turret
can be moved left and right using the keyboard. The turret can fire bullets
at the aliens, but only one bullet at a time can be in flight. If the bullet
hits an alien, the alien dies and is removed. The player is awarded ten points
for each alien that is killed. The player starts out with three turrets.

### Additional Rules
If the player successfully destroys all the aliens before they reach the bottom
of the screen, a new wave appears at the top.

For each new wave of aliens, they become a little bit faster, and a little bit
more agressive in dropping bombs.

### Display
At the very top of the screen, there's a panel showing how many turrets the
player has left, how many waves of aliens have been killed, and how many
points he has accumulated.

### Game Over
When the game ends, a message on the screen let's the player know so, and
pressing any button will restart the game.
