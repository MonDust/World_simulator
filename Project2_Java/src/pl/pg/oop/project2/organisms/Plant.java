package pl.pg.oop.project2.organisms;

import javax.swing.*;
import java.awt.*;
import java.util.Random;

public abstract class Plant extends Organism {
    protected static final int THE_FLOOR_OF_SPREAD = 10;
    protected Plant(World world, Point position) {
        super(world, position);
        IsAnimal = false;
    }

    public boolean action() {
        Random random = new Random();
        int ProbabilityOfSpread = random.nextInt(100);
        if(ProbabilityOfSpread < THE_FLOOR_OF_SPREAD) {
            Point newPosition = getNewPosition();
            if(newPosition.x == -1) return false;
            if(world.checkIfNotOccupied(newPosition)) {
                world.AddOrganism(TypeOfOrganism, newPosition);
                world.addComment(this + " spread.");
                return true;
            }
        }
        return false;
    }

    @Override
    public ImageIcon getImage() {
        String FileName = "Images/"+ this +".jpg";
        return new ImageIcon(FileName);
    }
}
