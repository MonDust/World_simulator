package pl.pg.oop.project2.organisms;
import javax.swing.*;
import java.awt.*;
import java.util.Random;

public abstract class Animal extends Organism {
    protected static final int THE_FLOOR_OF_ESCAPE_ANTELOPE = 50;
    protected Animal(World world, Point position) {
        super(world, position);
    }

    protected Animal(World world, Point position, int strength) {
        super(world, position, strength);
    }


    public boolean action() {
        Point newPosition = getNewPosition();
        if(newPosition.x == -1) return false;
        prevPosition = position;
        position = newPosition;
        TryToGoToPosition();
        return true;
    }
    public void MultiplyOrganism() {
        Point newPosition = getNewPosition();
        if(newPosition.x != -1) {
            if(world.checkIfNotOccupied(newPosition)) {
                world.AddOrganism(TypeOfOrganism, newPosition);
                world.addComment(this + " multiplied.");
            }
        }
    }

    @Override
    public void collision(Organism AttackerOrganism) {
        Random random = new Random();
        int ProbabilityOfEscape = random.nextInt(100);
        AttackerOrganism.PutIntoWorld();
        if(TypeOfOrganism == AttackerOrganism.TypeOfOrganism) {
            MultiplyOrganism();
            return;
        }
        if(ProbabilityOfEscape < THE_FLOOR_OF_ESCAPE_ANTELOPE) {
            Point newPosition = getNewPosition();
            if(newPosition.x != -1 && world.checkIfNotOccupied(newPosition)) {
                if (AttackerOrganism.TypeOfOrganism == OrganismsEnum.ANTELOPE) {
                    AttackerOrganism.ChangePosition(newPosition);
                    AttackerOrganism.PutIntoWorld();
                    PutIntoWorld();
                    world.addComment(AttackerOrganism + " escaped.");
                    return;
                } else if (TypeOfOrganism == OrganismsEnum.ANTELOPE) {
                    ChangePosition(newPosition);
                    PutIntoWorld();
                    world.addComment(this + " escaped.");
                    return;
                }
            }
        }
        if(strength > AttackerOrganism.strength) {
            PutIntoWorld();
            if(AttackerOrganism.TypeOfOrganism != OrganismsEnum.HUMAN)
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
     public ImageIcon getImage() {
        String FileName = "Images/"+ this +".jpg"; // toString
        return new ImageIcon(FileName);
    }
}
