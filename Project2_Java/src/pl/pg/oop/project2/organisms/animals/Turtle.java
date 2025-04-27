package pl.pg.oop.project2.organisms.animals;

import pl.pg.oop.project2.organisms.Animal;
import pl.pg.oop.project2.organisms.Organism;
import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;
import java.util.Random;

public class Turtle extends Animal {
    private final static int DEFAULT_INITIATIVE = 1;
    private final static int DEFAULT_STRENGTH = 2;
    private final static int TURTLE_DEFENSE = 5;
    private final static int THE_FLOOR_OF_TURTLE_MOVEMENT = 75;
    public Turtle(World world, Point position) {
        super(world, position);
        this.TypeOfOrganism = OrganismsEnum.TURTLE;
        this.initiative = DEFAULT_INITIATIVE;
        this.strength = DEFAULT_STRENGTH;
    }

    public Turtle(World world, Point position, int strength) {
        super(world, position, strength);
        this.TypeOfOrganism = OrganismsEnum.TURTLE;
        this.initiative = DEFAULT_INITIATIVE;
    }

    @Override
    public void collision(Organism AttackerOrganism) {
        Random random = new Random();
        int ProbabilityOfEscape = random.nextInt(100);
        AttackerOrganism.PutIntoWorld();
        if(TypeOfOrganism == AttackerOrganism.getTypeOfOrganism()) {
            MultiplyOrganism();
            return;
        }
        if(ProbabilityOfEscape < THE_FLOOR_OF_ESCAPE_ANTELOPE) {
            Point newPosition = getNewPosition();
            if(newPosition.x != -1 && world.checkIfNotOccupied(newPosition)) {
                if (AttackerOrganism.getTypeOfOrganism() == OrganismsEnum.ANTELOPE) {
                    AttackerOrganism.ChangePosition(newPosition);
                    AttackerOrganism.PutIntoWorld();
                    PutIntoWorld();
                    world.addComment(AttackerOrganism + " escaped.");
                    return;
                }
            }
        }
        if(TURTLE_DEFENSE > AttackerOrganism.getStrength()) {
            AttackerOrganism.exchangePositions();
            AttackerOrganism.PutIntoWorld();
            PutIntoWorld();
            world.addComment(this + " deflected the attack.");
        }
        if(strength > AttackerOrganism.getStrength()) {
            PutIntoWorld();
            if(AttackerOrganism.getTypeOfOrganism() != OrganismsEnum.HUMAN)
                world.RemoveOrganismFromList(AttackerOrganism);
            else
                world.DeleteHuman();
            world.addComment(this + " won with " + AttackerOrganism);
        }
        else {
            if(this.TypeOfOrganism != OrganismsEnum.HUMAN)
                world.RemoveOrganismFromList(this);
            else
                world.DeleteHuman();
            world.addComment(AttackerOrganism + " won with " + this);
        }
    }

    @Override
    public boolean action() {
        Point newPosition = getNewPosition();
        Random random = new Random();
        int PossibilityOfMovement = random.nextInt(100);
        if(newPosition.x == -1 || PossibilityOfMovement < THE_FLOOR_OF_TURTLE_MOVEMENT) return false;
        prevPosition = position;
        position = newPosition;
        TryToGoToPosition();
        return true;
    }

    @Override
    public String toString() {
        return "Turtle";
    }
}
