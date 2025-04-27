package pl.pg.oop.project2.organisms.animals;

import pl.pg.oop.project2.organisms.Animal;
import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;
import java.util.Random;

public class Fox extends Animal {
    private final static int DEFAULT_INITIATIVE = 7;
    private final static int DEFAULT_STRENGTH = 3;

    private int NumberOfPossiblePositions = 4;
    private int[] Moves = {0, 1, 2, 3};
    public Fox(World world, Point position) {
        super(world, position);
        TypeOfOrganism = OrganismsEnum.FOX;
        initiative = DEFAULT_INITIATIVE;
        strength = DEFAULT_STRENGTH;
    }

    public Fox(World world, Point position, int strength) {
        super(world, position, strength);
        TypeOfOrganism = OrganismsEnum.FOX;
        initiative = DEFAULT_INITIATIVE;
    }

    private Point checkPositionFox(Point curPosition, int iMove) {
        Point newPosition = new Point(-1, -1);
        if (world.checkIfNotOccupied(curPosition)) {
            newPosition = curPosition;
        }
        else {
            if (strength >= world.getOrganismInPosition(new Point(curPosition)).getStrength()) {
                newPosition = curPosition;
            }
            else {
                Moves[iMove] = -1;
                for(int i = iMove + 1; i < 4; i++ ) {
                    Moves[i]--;
                }
                NumberOfPossiblePositions--;
            }
        }
        return newPosition;
    }

    private Point getNewFoxPosition() {
        Random random = new Random();
        Point newPosition = new Point(-1, -1), curPosition;
        NumberOfPossiblePositions = 4;
        for(int i = 0; i < NumberOfPossiblePositions; i++) {
            Moves[i] = i;
        }

        while (true) {
            int move = random.nextInt(NumberOfPossiblePositions);
            if (move == Moves[0] && position.x >= step) {
                newPosition = checkPositionFox(new Point(position.x - step, position.y), 0);
            }
            else if (move == Moves[1] && position.x < world.getSizeOfWorld().x - step) {
                newPosition = checkPositionFox(new Point(position.x + step, position.y), 1);
            }
            else if (move == Moves[2] && position.y >= step) {
                newPosition = checkPositionFox(new Point(position.x, position.y - step), 2);
            }
            else if (move == Moves[3] && position.y < world.getSizeOfWorld().y - step) {
                newPosition = checkPositionFox(new Point(position.x, position.y + step), 3);
            }
            else { break; }
            if (NumberOfPossiblePositions <= 0 || newPosition.x != -1) break;
        }
        return newPosition;
    }

    @Override
    public boolean action() {
        Point newPosition = getNewFoxPosition();
        if(newPosition.x == -1) return false;
        prevPosition = position;
        position = newPosition;
        TryToGoToPosition();
        return true;
    }

    @Override
    public String toString() {
        return "Fox";
    }
}
