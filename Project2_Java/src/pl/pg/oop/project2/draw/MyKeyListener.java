package pl.pg.oop.project2.draw;

import pl.pg.oop.project2.organisms.move;

import java.awt.event.*;

public class MyKeyListener implements KeyListener {
    private final BoardPanel board;
    public MyKeyListener(BoardPanel board) {
        this.board = board;
    }

    @Override
    public void keyPressed(KeyEvent e) {
        int KeyCode = e.getKeyCode();
        switch (KeyCode) {
            case(KeyEvent.VK_ENTER) -> board.world.makeTurn(move.NOMOVE);
            case(KeyEvent.VK_RIGHT) -> board.world.makeTurn(move.RIGHT);
            case(KeyEvent.VK_LEFT) -> board.world.makeTurn(move.LEFT);
            case(KeyEvent.VK_UP) -> board.world.makeTurn(move.UP);
            case(KeyEvent.VK_DOWN) -> board.world.makeTurn(move.DOWN);
        }
        board.loadImageIcons();
        board.repaint();
    }

    @Override
    public void keyReleased(KeyEvent e) {
        // Not used
    }

    @Override
    public void keyTyped(KeyEvent e) {
        // Not used
    }
}
