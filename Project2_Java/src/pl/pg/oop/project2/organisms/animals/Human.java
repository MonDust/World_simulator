package pl.pg.oop.project2.organisms.animals;

import pl.pg.oop.project2.organisms.Animal;
import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.World;
import pl.pg.oop.project2.organisms.move;

import java.awt.*;

public class Human extends Animal {
    private final static int DEFAULT_INITIATIVE = 4;
    private int DEFAULT_STRENGTH = 5;
    private boolean IsAbilityOn;
    private int NumberOfRoundsUntilPossibleActivation = 0; // needs to be saved
    private final static int NumberOfTurnsWithAbilityON = 5;

    private move CurrentMove = move.NOMOVE;
    public Human(World world, Point position) {
        super(world, position);
        this.TypeOfOrganism = OrganismsEnum.HUMAN;
        this.initiative = DEFAULT_INITIATIVE;
        this.strength = DEFAULT_STRENGTH;
        this.IsAbilityOn = false;
    }

    public Human(World world, Point position, int strength) {
        super(world, position, strength);
        this.TypeOfOrganism = OrganismsEnum.HUMAN;
        this.initiative = DEFAULT_INITIATIVE;
        this.IsAbilityOn = false;
    }

    public Human(World world, Point position, int strength, int DefaultStrength, boolean IsAbilityOn, int nUntilActivation ) {
        super(world, position, strength);
        this.DEFAULT_STRENGTH = DefaultStrength;
        this.TypeOfOrganism = OrganismsEnum.HUMAN;
        this.initiative = DEFAULT_INITIATIVE;
        this.IsAbilityOn = IsAbilityOn;
        this.NumberOfRoundsUntilPossibleActivation = nUntilActivation;
    }

    /**
     * Try to turn on the Special Ability.
     * @return message about the Special Ability.
     */
    public String SpecialAbility() {
        String message;
        if (NumberOfRoundsUntilPossibleActivation == 0 && !IsAbilityOn) {
            DEFAULT_STRENGTH = strength;
            strength += NumberOfTurnsWithAbilityON;
            IsAbilityOn = true;
            message = "Special Ability Activated. Current strength: "+strength
                    +".\nWill decrease until strength is back to normal.";
        }
        else if(NumberOfRoundsUntilPossibleActivation != 0) {
            message = "Cannot activate Special Ability.\nWill be possible in: "
                    +NumberOfRoundsUntilPossibleActivation+" turns.";
        }
        else {
            message = "Ability is already on. Current strength: "+strength+".";
        }
        return message;
    }

    /**
     * Decrease the strength added by Ability.
     */
    private void DecreaseAbility() {
        if (IsAbilityOn) {
            strength -= 1;
            if (strength <= DEFAULT_STRENGTH) {
                NumberOfRoundsUntilPossibleActivation = 5;
                IsAbilityOn = false;
            }
        }
    }

    /**
     * Decrease the counter that informs if the Ability can be activated.
     */
    private void DecreaseAbilityCounter() {
        if (NumberOfRoundsUntilPossibleActivation != 0) NumberOfRoundsUntilPossibleActivation--;
    }

    /**
     * Handling Special Ability - decrease Ability or decrease the counter that informs if the Ability can be activated.
     */
    public void handleSpecialAbility() {
        DecreaseAbility();
        DecreaseAbilityCounter();
    }

    /**
     * Change Current move - human can move left, right, up, down or make no move.
     * @param NewMove The move that human will make.
     */
    public void ChangeMove(move NewMove) {
        CurrentMove = NewMove;
    }

    /**
     * @return New Position for Human based on CurrentMove.
     */
    private Point getNewHumanPosition() {
        Point newPosition;
        if (CurrentMove == move.LEFT && position.x >= step) { // Direction Left
            newPosition = new Point(position.x - step, position.y);
        }
        else if (CurrentMove == move.RIGHT && position.x < world.getSizeOfWorld().x - step) { // Direction Right
            newPosition = new Point(position.x + step, position.y);
        }
        else if (CurrentMove == move.UP && position.y >= step) { // Direction Up
            newPosition = new Point(position.x, position.y - step);
        }
        else if(CurrentMove == move.DOWN && position.y < world.getSizeOfWorld().y - step) { // Direction Down
            newPosition = new Point(position.x, position.y + step);
        }
        else {
            return new Point(-1, -1);
        }
        return newPosition;
    }

    @Override
    public boolean action() {
        Point newPosition = getNewHumanPosition();
        if(newPosition.x == -1) return false;
        prevPosition = position;
        position = newPosition;
        TryToGoToPosition();
        return true;
    }

    @Override
    public String toString() {
        return "Human";
    }

    @Override
    public String SaveOrganism() {
        return this.TypeOfOrganism + " " + this.position.x + " " + this.position.y + " "
                + this.prevPosition.x + " " + this.prevPosition.y + " " + this.strength + " "
                + this.DEFAULT_STRENGTH + " " + this.IsAbilityOn + " "
                + this.NumberOfRoundsUntilPossibleActivation + "\n";
    }

}
