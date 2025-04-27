package pl.pg.oop.project2.draw;

import pl.pg.oop.project2.organisms.*;
import pl.pg.oop.project2.*;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileWriter;
import java.io.FilenameFilter;
import java.io.IOException;

public class MyFrame extends JFrame {
    final static private Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
    final static private Point SizeOfTheScreen = new Point((int)screenSize.getWidth(),(int)screenSize.getHeight());

    final private World world;

    private final JPanel mainPanel;

    private JPanel buttonPanel;

    private BoardPanel boardPanel;

    private final SaveAndLoad saveAndLoad;
    public MyFrame(World world) {
        super("The Board");
        this.world = world;
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mainPanel = new JPanel();
        setMainPanel();
        this.add(mainPanel);
        this.pack();
        this.setVisible(true);
        saveAndLoad = new SaveAndLoad(world);
    }

    private void setMainPanel() {
        mainPanel.setLayout(new BorderLayout());
        boardPanel = new BoardPanel(SizeOfTheScreen, world.getSizeOfWorld(), world);
        mainPanel.add(boardPanel, BorderLayout.CENTER);
        setButtonPanel();
    }

    private void setButtonPanel() {
        buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout());
        setButtons();
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);
    }

    public void focusBoardPanel() {
        boardPanel.setFocusable(true);
        boardPanel.requestFocusInWindow();
    }

    private void setButtons() {
        JButton saveButton = new JButton("Save");
        saveButton.addActionListener(e -> {
            saveFile();
            focusBoardPanel();
        });
        buttonPanel.add(saveButton);

        JButton loadButton = new JButton("Load");
        loadButton.addActionListener(e -> {
            String FileName = showFileList();
            if(FileName != null) {
                saveAndLoad.LoadOrganisms(FileName);
            }
            boardPanel.loadImageIcons();
            boardPanel.repaint();
            focusBoardPanel();
        });
        buttonPanel.add(loadButton);

        JButton showControlsButton = new JButton("Show Controls");
        showControlsButton.addActionListener(e -> {
            showControls();
            focusBoardPanel();
        });
        buttonPanel.add(showControlsButton);

        JButton specialAbilityButton = new JButton("Special Ability");
        specialAbilityButton.addActionListener(e -> {
            turnSpecialAbilityOn();
            focusBoardPanel();
        });
        buttonPanel.add(specialAbilityButton);

        JButton turnButton = new JButton("Show Turn");
        turnButton.addActionListener(e -> {
            showTurn();
            focusBoardPanel();
        });
        buttonPanel.add(turnButton);
    }

    private void showTurn() {
        world.printComments();
    }

    private void turnSpecialAbilityOn() {
        if(!world.isHumanAlive()) {
            String message = "Big Warrior has died.";
            JOptionPane.showMessageDialog(null, message, "Sad News", JOptionPane.INFORMATION_MESSAGE);
        }
        else {
            String message = world.specialAbilityOn();
            JOptionPane.showMessageDialog(null, message, "About Ability", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    private static void showControls() {
        String message = "Enter - Next turn\nArrows - Move human";
        JOptionPane.showMessageDialog(null, message, "Controls", JOptionPane.INFORMATION_MESSAGE);
    }

    private static String showFileList() {
        File currentDir = new File(".");
        File saveFilesDir = new File(currentDir.getAbsolutePath() + File.separator + "SaveFiles");
        File[] files = saveFilesDir.listFiles(new TxtFileFilter());

        if (files != null && files.length > 0) {
            String[] fileNames = new String[files.length];
            for (int i = 0; i < files.length; i++) {
                fileNames[i] = files[i].getName();
            }

            String selectedFileName = (String) JOptionPane.showInputDialog(null, "Select a File:", "File List",
                    JOptionPane.PLAIN_MESSAGE, null, fileNames, fileNames[0]);

            if (selectedFileName != null && !selectedFileName.isEmpty()) {
                System.out.println("Selected File: " + selectedFileName);
                return selectedFileName;
            }
        } else {
            JOptionPane.showMessageDialog(null, "No txt files found in the 'SaveFiles' directory.", "File List",
                    JOptionPane.INFORMATION_MESSAGE);
        }
        return null;
    }

    private static class TxtFileFilter implements FilenameFilter {
        @Override
        public boolean accept(File dir, String name) {
            return name.toLowerCase().endsWith(".txt");
        }
    }

    private void saveFile() {
        saveAndLoad.makeSaveFile();

    }
}
