package pl.pg.oop.project2.organisms;

import pl.pg.oop.project2.organisms.animals.*;

import java.awt.*;

import java.util.*;
import java.util.List;

/**
 * World in which the Organisms live.
 */
public class World implements NamesOfOrganisms{
    private final List<Organism> ListOfOrganisms;

    private List<String> Commentator;
    private Human ABigWarrior;
    private final Organism[][] MapOfOrganisms;
    private int NumberOfOrganisms;
    private final Point SizeOfWorld;
    private final static double PERCENT_OF_THE_WORLD = 0.1;

    private int Turn;

    /**
     * Initializes the world with ListOfOrganisms and MapOfOrganisms.
     * @param SizeOfTheWorld Size of The world nxm.
     */
    public World(Point SizeOfTheWorld) {
        this.ListOfOrganisms = new ArrayList<>();
        this.Commentator = new ArrayList<>();
        this.SizeOfWorld = SizeOfTheWorld;
        this.MapOfOrganisms = new Organism[SizeOfWorld.x][SizeOfWorld.y];
        this.NumberOfOrganisms = 0;
        this.ABigWarrior = null;
        for(int i = 0; i < SizeOfWorld.x; i++) {
            for(int j = 0; j < SizeOfWorld.y; j++) {
                MapOfOrganisms[i][j] = null;
            }
        }
        this.Turn = 1;
        InitializeOrganisms();
    }

    /**
     * Checks if Human is Alive and well.
     * @return If Human is Alive returns true, else false.
     */
    public boolean isHumanAlive() {
        return (ABigWarrior != null);
    }

    /**
     * Turns on a special ability of Human.
     */
    public String specialAbilityOn() {
        return ABigWarrior.SpecialAbility();
    }

    /**
     * Sorts the List of Organisms by the Organisms initiative.
     * @param organisms List Of Organisms to be sorted.
     */
    private static void sortOrganismsByInitiative(List<Organism> organisms) {
        organisms.sort((o1, o2) -> {
            // Sort in descending order based on initiative
            return Integer.compare(o2.getInitiative(), o1.getInitiative());
        });
    }

    /**
     * Clears the map of world (organisms) by assigning every place with null.
     */
    private void clearWorld() {
        for(int i = 0; i < SizeOfWorld.x; i++) {
            for(int j = 0; j < SizeOfWorld.y; j++) {
                MapOfOrganisms[i][j] = null;
            }
        }
    }

    public void deleteWorld() {
        Commentator.clear();
        ListOfOrganisms.clear();
        clearWorld();
        NumberOfOrganisms = 0;
        ABigWarrior = null;
        Turn = 1;
    }

    /**
     * Initializes all Organisms that are in the ListOfOrganisms into MapOfOrganisms (places them into world).
     * Before the procedure is done also calls clearWorld() - cleaning the world.
     */
    private void initializeAllOrganism() {
        clearWorld();
        if(ListOfOrganisms != null) {
            for (Organism organism : ListOfOrganisms) {
                Point orgPosition = organism.getPosition();
                MapOfOrganisms[orgPosition.x][orgPosition.y] = organism;
            }
        }
        if(ABigWarrior != null) {
            Point warriorPosition = ABigWarrior.getPosition();
            MapOfOrganisms[warriorPosition.x][warriorPosition.y] = ABigWarrior;
        }
    }

    /**
     * Adds comment to Commentator.
     * @param message A comment to add.
     */
    public void addComment(String message) {
        Commentator.add(message);
    }

    public void printComments() {
        if(Commentator == null) {
            System.out.println("Nothing happened.");
        }
        else {
            for (String comment : Commentator) {
                System.out.println(comment);
            }
        }
    }

    public List<String> makeSaveFileContents() {
        List<String> saveFileList = new ArrayList<>();
        if(ABigWarrior != null) {
            saveFileList.add(ABigWarrior.SaveOrganism());
        }
        if(ListOfOrganisms != null) {
            for (Organism organism : ListOfOrganisms) {
                saveFileList.add(organism.SaveOrganism());
            }
        }
        return saveFileList;
    }

    private void clearComments() {
        Commentator.clear();
    }

    /**
     * @return The list of comments on what happened in the world.
     */
    public List<String> getCommentator() {
        return Commentator;
    }

    /**
     * Makes the next turn, takes the parameters that indicates in which direction will the human move.
     * @param HumanMove Next move of the human - right, left, up, down or no move.
     */
    public void makeTurn(move HumanMove) {
        clearComments();
        System.out.println("Turn: " + Turn);
        sortOrganismsByInitiative(ListOfOrganisms);
        boolean HumanFlag = true;
        NumberOfOrganisms = ListOfOrganisms.size();
        for (int i = 0; i < NumberOfOrganisms; i++) {
            Organism organism = ListOfOrganisms.get(i);
            if(ABigWarrior != null) {
                if (organism.getInitiative() < ABigWarrior.getInitiative() && HumanFlag) {
                    ABigWarrior.ChangeMove(HumanMove);
                    ABigWarrior.action();
                    HumanFlag = false;
                }
            }
            organism.action();
        }
        if(ABigWarrior != null) ABigWarrior.handleSpecialAbility();
        Turn++;
        initializeAllOrganism();
    }

    /**
     * Removes the provided Organism from ListOfOrganisms.
     * ! Does not remove the Organism from the world, needs to be done by nullThePosition().
     * @param OrganismToRemove Organism that needs to be removed.
     */
    public void RemoveOrganismFromList(Organism OrganismToRemove) {
        ListOfOrganisms.remove(OrganismToRemove);
        NumberOfOrganisms--;
    }

    /**
     * @return the size of world nxm as Point
     */
    public Point getSizeOfWorld() {
        return SizeOfWorld;
    }

    /**
     * Gets the Organism at position ThePosition.
     * @param ThePosition The position of Organism.
     * @return The Organism at provided position in MapOfOrganisms (world).
     */
    public Organism getOrganismInPosition(Point ThePosition) {
        return MapOfOrganisms[ThePosition.x][ThePosition.y];
    }

    /**
     * Checks if in the provided position is the provided Organism.
     * @param TheOrganism The Organism that we are searching for.
     * @param ThePosition The position that we are checking.
     * @return True if the Organism is in the position, else false.
     */
    public boolean IsEqualInThePosition(Organism TheOrganism, Point ThePosition) {
        if(ThePosition.x == -1) return false;
        if(MapOfOrganisms[ThePosition.x][ThePosition.y] == null) return false;
        return MapOfOrganisms[ThePosition.x][ThePosition.y].equals(TheOrganism);
    }

    /**
     * Delete the Organism from the world. Null the provided position in MapOfOrganisms.
     * @param ThePosition The position that we want to null.
     */
    public void nullThePosition(Point ThePosition) {
        MapOfOrganisms[ThePosition.x][ThePosition.y] = null;
    }

    /**
     * Put already existing Organism into the world into the specified position (position is specified as one of the variables of TheOrganism).
     * @param TheOrganism Organism that we want to put into the MapOfOrganisms.
     */
    public void putEstablishedOrganismToWorld(Organism TheOrganism) {
        Point ThePosition = TheOrganism.getPosition();
        MapOfOrganisms[ThePosition.x][ThePosition.y] = TheOrganism;
    }

    /**
     * Check if the position is not occupied in the MapOfOrganisms (world).
     * @param ThePosition The position that we want to check.
     * @return True if not occupied, false if occupied.
     */
    public boolean checkIfNotOccupied(Point ThePosition) {
        return MapOfOrganisms[ThePosition.x][ThePosition.y] == null;
    }

    /**
     * Provides you with a random Organism from OrganismsEnum.
     * @return Random OrganismsEnum.
     */
    private static OrganismsEnum getRandomOrganism() {
        Random random = new Random();
        return OrganismsEnum.values()[random.nextInt(OrganismsEnum.values().length)];
    }

    /**
     * Provide a random position within world limitations.
     * @return Random Position.
     */
    private Point getRandomPosition() {
        Random random = new Random();
        int valueX = random.nextInt(SizeOfWorld.x);
        int valueY = random.nextInt(SizeOfWorld.y);
        return new Point(valueX, valueY);
    }

    /**
     * Adds ones instance of all Organisms (except Human).
     */
    private void AddOneInstanceOfAll() {
        for(int i = 0; i < NumberOfOrg; i++) {
            AddOrganism(OrganismsEnum.values()[i]);
        }
    }

    /**
     * Add random Organism in the random position to the world.
     */
    public void AddOrganism() {
        Point position = getRandomPosition();
        int TryTenTimes = 10, i = 0;
        while(MapOfOrganisms[position.x][position.y] != null) {
            if(i == TryTenTimes) return;
            position = getRandomPosition();
            i++;
        }
        OrganismsEnum OrganismName = getRandomOrganism();
        Organism NewOrganism;
        NewOrganism = Organism.GetOrganism(OrganismName, this, position);
        if(NewOrganism != null) {
            ListOfOrganisms.add(NewOrganism);
            MapOfOrganisms[position.x][position.y] = NewOrganism;
        }
    }

    /**
     * Add Organism in the random position to the world.
     * @param OrganismName Type of Organism to add.
     */
    public void AddOrganism(OrganismsEnum OrganismName) {
        Point position = getRandomPosition();
        int TryTenTimes = 10, i = 0;
        while(MapOfOrganisms[position.x][position.y] != null) {
            if(i == TryTenTimes) return;
            position = getRandomPosition();
            i++;
        }
        Organism NewOrganism;
        NewOrganism = Organism.GetOrganism(OrganismName, this, position);
        if(NewOrganism != null) {
            ListOfOrganisms.add(NewOrganism);
            MapOfOrganisms[position.x][position.y] = NewOrganism;
        }
    }

    /**
     * Add random Organism in the position to the world.
     * @param OrganismName Type of Organism to add.
     * @param position Position at which the organism will be added.
     */
    public void AddOrganism(OrganismsEnum OrganismName, Point position) {
        Organism NewOrganism;
        NewOrganism = Organism.GetOrganism(OrganismName, this, position);
        if(NewOrganism != null) {
            ListOfOrganisms.add(NewOrganism);
            MapOfOrganisms[position.x][position.y] = NewOrganism;
        }
    }

    /**
     * Add random Organism in the random position with certain strength to the world.
     * @param OrganismName Type of Organism to add.
     * @param position Position at which the organism will be added.
     * @param strength Strength of Organism thad needs to be added.
     */
    public void AddOrganism(OrganismsEnum OrganismName, Point position, int strength) {
        Organism NewOrganism;
        NewOrganism = Organism.GetOrganism(OrganismName, this, position, strength);
        if(NewOrganism != null) {
            ListOfOrganisms.add(NewOrganism);
            MapOfOrganisms[position.x][position.y] = NewOrganism;
        }
    }

    /**
     * Delete the human, make ABigWarrior null.
     */
    public void DeleteHuman() {
       ABigWarrior = null;
    }

    /**
     * Add human to the random position to the world.
     */
    private void AddHuman() {
        Point position = getRandomPosition();
        ABigWarrior = new Human(this, position);
        MapOfOrganisms[position.x][position.y] = ABigWarrior;
    }

    /**
     * Add human to the position with certain strength to the world.
     * @param position Position.
     * @param strength The strength of Human.
     * @param DefStrength Default strength of Human.
     * @param IsAbilityOn Is Ability on.
     * @param nUntilActivation How much until possible activation.
     */
    public void AddHuman(Point position, int strength, int DefStrength, boolean IsAbilityOn, int nUntilActivation) {
        ABigWarrior = new Human(this, position, strength, DefStrength, IsAbilityOn, nUntilActivation);
        MapOfOrganisms[position.x][position.y] = ABigWarrior;
    }

    /**
     * Initialize random Organisms to the world.
     */
    private void InitializeOrganisms() {
        int maxSize = SizeOfWorld.x * SizeOfWorld.y - 1;
        int numberOfAnimals = (int)(maxSize*PERCENT_OF_THE_WORLD);
        AddHuman();
        AddOneInstanceOfAll();
        for(int i = 0; i < numberOfAnimals; i++) {
            AddOrganism();
        }
    }

    /**
     * Print the map by System.out.println().
     */
    public void printMap() {
        for(int i = 0; i < SizeOfWorld.x; i++) {
            for(int j = 0; j < SizeOfWorld.y; j++) {
                System.out.print(MapOfOrganisms[i][j] + " ");
            }
            System.out.println();
        }
    }
}
