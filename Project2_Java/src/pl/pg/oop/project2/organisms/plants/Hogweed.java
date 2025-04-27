package pl.pg.oop.project2.organisms.plants;

import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;

public class Hogweed extends DangerousPlant {
    private final static int DEFAULT_STRENGTH = 10;
    public Hogweed(World World_, Point Position_) {
        super(World_, Position_);
        this.TypeOfOrganism = OrganismsEnum.HOGWEED;
        this.strength = DEFAULT_STRENGTH;
    }

    @Override
    public String toString() {
        return "Hogweed";
    }

    private void KillInPosition(Point positionToKill) {
        if (!world.checkIfNotOccupied(positionToKill)) {
            if(world.getOrganismInPosition(positionToKill).isOrganismAnAnimal()) {
                world.addComment(this + " killed "+ world.getOrganismInPosition(positionToKill));
                if(world.getOrganismInPosition(positionToKill).getTypeOfOrganism() == OrganismsEnum.HUMAN) {
                    world.DeleteHuman();
                }
                else {
                    world.RemoveOrganismFromList(world.getOrganismInPosition(positionToKill));
                }
                world.nullThePosition(positionToKill);
            }
        }
    }

    /**
     * Kill all the Organisms around.
     */
    private void KillAround() {
        Point CheckedPosition;
        Point WorldSize = world.getSizeOfWorld();
        if (position.x < WorldSize.x - step) {
            CheckedPosition = new Point(position.x + step,position.y);
            KillInPosition(CheckedPosition);
        }
        if (position.x >= step) {
            CheckedPosition = new Point(position.x - step,position.y);
            KillInPosition(CheckedPosition);
        }
        if (position.y < WorldSize.y - step) {
            CheckedPosition = new Point(position.x,position.y + step);
            KillInPosition(CheckedPosition);
        }
        if (position.y >= step) {
            CheckedPosition = new Point(position.x,position.y - step);
            KillInPosition(CheckedPosition);
        }
    }

    @Override
    public boolean action() {
        boolean Flag = super.action();
        KillAround();
        return Flag;
    }
}
