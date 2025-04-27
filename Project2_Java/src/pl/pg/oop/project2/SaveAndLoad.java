package pl.pg.oop.project2;

import pl.pg.oop.project2.organisms.*;

import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class SaveAndLoad {
    private static World world;

    public SaveAndLoad(World world_) {
        world = world_;
    }

    public void LoadOrganisms(String FileName) {
        try (BufferedReader br = new BufferedReader(new FileReader("SaveFiles"+File.separator+FileName))) {
            String line;
            world.deleteWorld();
            while ((line = br.readLine()) != null) {
                String[] lineSplit = line.split(" ");
                OrganismsEnum organismType = OrganismsEnum.valueOf(lineSplit[0]);
                Point position = new Point(Integer.parseInt(lineSplit[1]),Integer.parseInt(lineSplit[2]));
                Point prevPosition = new Point(Integer.parseInt(lineSplit[3]),Integer.parseInt(lineSplit[4]));
                int strength = Integer.parseInt(lineSplit[5]);
                if(organismType == OrganismsEnum.HUMAN) {
                    int defStrength = Integer.parseInt(lineSplit[6]);
                    boolean isAbility = Boolean.parseBoolean(lineSplit[7]);
                    int nUntilActivation = Integer.parseInt(lineSplit[8]);
                    world.AddHuman(position,strength,defStrength,isAbility,nUntilActivation);
                }
                else {
                    world.AddOrganism(organismType, position, strength);
                }

            }
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }

    public void makeSaveFile() {
        String fileName = JOptionPane.showInputDialog(null, "Enter the file name:", "Save File",
                JOptionPane.PLAIN_MESSAGE);

        if (fileName != null && !fileName.isEmpty()) {
            List<String> Contents = world.makeSaveFileContents();

            File currentDir = new File(".");
            File saveFilesDir = new File(currentDir.getAbsolutePath() + File.separator + "SaveFiles");
            if (!saveFilesDir.exists()) {
                if(!saveFilesDir.mkdirs()) return;
            }

            File newFile = new File(saveFilesDir.getAbsolutePath() + File.separator + fileName + ".txt");
            try (FileWriter writer = new FileWriter(newFile)) {
                for(String content: Contents) {
                    writer.write(content);
                }
                writer.flush();

                JOptionPane.showMessageDialog(null, "File saved successfully.", "Save File",
                        JOptionPane.INFORMATION_MESSAGE);
            } catch (IOException e) {
                JOptionPane.showMessageDialog(null, "Error occurred while saving the file.", "Save File",
                        JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}
