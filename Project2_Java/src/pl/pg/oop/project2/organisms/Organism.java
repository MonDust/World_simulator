package pl.pg.oop.project2.organisms;

import pl.pg.oop.project2.organisms.animals.*;
import pl.pg.oop.project2.organisms.plants.*;

import javax.swing.*;
import java.util.Random;
import java.awt.*;

public abstract class Organism {
    protected static World world;
    protected Point position;
    protected Point prevPosition;
    protected int strength = 0;
    protected int initiative = 0;
    protected int step = 1;
    protected OrganismsEnum TypeOfOrganism = OrganismsEnum.DEFAULT_ORGANISM;
    protected boolean IsAnimal = true;

    protected Organism(World world_, Point position) {
        world = world_;
        this.position = position;
        this.prevPosition  = new Point(-1, -1);
    }

    protected Organism(World world_, Point position, int strength) {
        world = world_;
        this.position = position;
        this.strength = strength;
        this.prevPosition  = new Point(-1, -1);
    }

    public int getInitiative() {
        return initiative;
    }
    public int getStrength() {
        return strength;
    }
    public Point getPrevPosition() { return prevPosition; }
    public Point getPosition() {return position; }

    public void exchangePositions() {
        Point tmp = new Point(position.x, position.y);
        position = prevPosition;
        prevPosition = tmp;
    }

    public void ChangePosition(Point newPosition) {
        prevPosition = position;
        position = newPosition;
    }

    public boolean IsEqualInThePrevPosition() {
        return world.IsEqualInThePosition(this,prevPosition);
    }
    public void PutIntoWorld() {
        if (IsEqualInThePrevPosition()) {
            world.nullThePosition(prevPosition);
        }
        world.putEstablishedOrganismToWorld(this);
    }
    public boolean isOrganismAnAnimal() {return IsAnimal; }
    public OrganismsEnum getTypeOfOrganism() {return TypeOfOrganism; }

    public void increaseStrength(int Increase) {
        strength += Increase;
    }

    public void increaseStrength() {
        strength += 1;
    }
    public void decreaseStrength() {
        strength -= 1;
    }

    public Point getNewPosition() {
        int NumberOfPossiblePositions = 4;
        Random random = new Random();
        int move = random.nextInt(NumberOfPossiblePositions);
        Point newPosition;
        if (move == 0 && position.x >= step) {// Direction Left
            newPosition = new Point(position.x - step, position.y);
        }
        else if (move == 1 && position.x < world.getSizeOfWorld().x - step) { // Direction Right
            newPosition = new Point(position.x + step, position.y);
        }
        else if (move == 2 && position.y >= step) { // Direction Up
            newPosition = new Point(position.x, position.y - step);
        }
        else if(move == 3 && position.y < world.getSizeOfWorld().y - step) { // Direction Down
            newPosition = new Point(position.x, position.y + step);
        }
        else {
            return new Point(-1, -1);
        }
        return newPosition;
    }

    public String SaveOrganism() {
        return this.TypeOfOrganism + " " + this.position.x + " " + this.position.y + " "
                + this.prevPosition.x + " " + this.prevPosition.y + " " + this.strength + "\n";
    }

    /**
     * Get new Organism based on OrganismEnum - Organism type.
     * @param organismType Type of Organism.
     * @param world World to which add Organism.
     * @param position A position at which add new Organism.
     * @return A new Organism initialized.
     */
    public static Organism GetOrganism(OrganismsEnum organismType, World world, Point position) {
        Organism NewOrganism = null;
        switch(organismType) {
            case WOLF -> NewOrganism = new Wolf(world, position);
            case FOX -> NewOrganism = new Fox(world, position);
            case SHEEP -> NewOrganism = new Sheep(world, position);
            case ANTELOPE -> NewOrganism = new Antelope(world, position);
            case TURTLE -> NewOrganism = new Turtle(world, position);
            case BELLADONNA -> NewOrganism = new Belladonna(world, position);
            case GRASS -> NewOrganism = new Grass(world, position);
            case SOW_THISTLE -> NewOrganism = new Sow_Thistle(world, position);
            case GUARANA -> NewOrganism = new Guarana(world, position);
            case HOGWEED -> NewOrganism = new Hogweed(world, position);
        }
        return  NewOrganism;
    }

    /**
     * Get Organism based on OrganismEnum - Organism type.
     * @param organismType Type of Organism.
     * @param world World to which add Organism.
     * @param position A position at which add new Organism.
     * @param strength Organisms strength.
     * @return A new Organism initialized.
     */
    public static Organism GetOrganism(OrganismsEnum organismType, World world, Point position, int strength) {
        Organism NewOrganism = null;
        switch(organismType) {
            case WOLF -> NewOrganism = new Wolf(world, position, strength);
            case FOX -> NewOrganism = new Fox(world, position, strength);
            case SHEEP -> NewOrganism = new Sheep(world, position, strength);
            case ANTELOPE -> NewOrganism = new Antelope(world, position, strength);
            case TURTLE -> NewOrganism = new Turtle(world, position, strength);
            case BELLADONNA -> NewOrganism = new Belladonna(world, position);
            case GRASS -> NewOrganism = new Grass(world, position);
            case SOW_THISTLE -> NewOrganism = new Sow_Thistle(world, position);
            case GUARANA -> NewOrganism = new Guarana(world, position);
            case HOGWEED -> NewOrganism = new Hogweed(world, position);
        }
        return  NewOrganism;
    }

    public void TryToGoToPosition() {
        if(world.checkIfNotOccupied(position)) {
            PutIntoWorld();
        }
        else {
            world.getOrganismInPosition(position).collision(this);
        }
    }
    public abstract boolean action();
    public void collision(Organism AttackerOrganism) {
        AttackerOrganism.PutIntoWorld();
        if(strength > AttackerOrganism.strength) {
            PutIntoWorld();
            if(AttackerOrganism.getTypeOfOrganism() == OrganismsEnum.HUMAN) {
                world.DeleteHuman();
            }
            world.RemoveOrganismFromList(AttackerOrganism);
            world.addComment(this + " won with " + AttackerOrganism);
        }
        else {
            world.RemoveOrganismFromList(this);
            world.addComment(AttackerOrganism + " won with " + this);
        }
    }


    public ImageIcon getImage() {
           String FileName = "Images/Ground.jpg";
        return new ImageIcon(FileName);
    }
}
