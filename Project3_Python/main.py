from World import World
from Visuals import Visuals
import random
from Organism import Point

if __name__ == "__main__":
    world = World(Point(10, 15))
    random.seed()
    visuals = Visuals(world)
    visuals.main()
