package com.tech.rex;


import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;


class MainPanel extends JPanel {
    private static JFrame frame = new JFrame("ResQBot");
    private JButton forward,left,right, backward, stopBot, connect, followMaster;
    private ArrayList<String> directionArray = new ArrayList<>();
    private ArrayList<Long> timestampArray = new ArrayList<>();
    private static String HOST_IP = "192.168.4.1";
    private static int PORT_NO=1987;

    private MainPanel() {
        try {
            UIManager.LookAndFeelInfo[] looks = UIManager.getInstalledLookAndFeels();
            UIManager.setLookAndFeel(looks[1].getClassName());
            SwingUtilities.updateComponentTreeUI(this);
        } catch(Exception ignored) {}

        bindWidgets();
        add(left);
        add(forward);
        add(right);
        add(backward);
        add(stopBot);
        add(connect);
        add(followMaster);
    }

    private void bindWidgets() {
        forward = new JButton("forward");
        forward.addActionListener(e -> {
            Main.writeCommand((int)'f',Main.socket);
            directionArray.add("forward");
            timestampArray.add(System.currentTimeMillis());
        });
        left = new JButton("left");
        left.addActionListener(e -> {
            Main.writeCommand((int)'l',Main.socket);
            directionArray.add("left");
            timestampArray.add(System.currentTimeMillis());
        });
        right = new JButton("right");
        right.addActionListener(e -> {
            Main.writeCommand((int)'r',Main.socket);
            directionArray.add("right");
            timestampArray.add(System.currentTimeMillis());
        });
        backward = new JButton("backward");
        backward.addActionListener(e -> {
            Main.writeCommand((int)'b',Main.socket);
            directionArray.add("backward");
            timestampArray.add(System.currentTimeMillis());
        });

        stopBot = new JButton("stop");
        stopBot.addActionListener(e -> {
            Main.writeCommand((int)'s',Main.socket);
            directionArray.add("stop");
            timestampArray.add(System.currentTimeMillis());
        });
        connect = new JButton("connect");
        connect.addActionListener(e -> {
            try {
                Main.socket = new Socket(HOST_IP,PORT_NO);
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        });
        followMaster = new JButton("followMaster");
        followMaster.addActionListener(e -> {
            try {
                followMaster();
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        });
    }

    private void followMaster() throws InterruptedException {
        int count = directionArray.size();
        for(int i=0; i<count - 1; i++) {
            Main.writeCommand((int)directionArray.get(i).charAt(0),Main.socket);
            long delay = timestampArray.get(i+1) - timestampArray.get(i);
            Thread.sleep(delay);
        }
        Main.writeCommand((int)'s',Main.socket);
        directionArray.clear();
        timestampArray.clear();
    }

    static void launch() {
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        frame.setBounds(new Rectangle(0, 0, dim.width, dim.height));
        frame.setPreferredSize(dim);
        MainPanel panel = new MainPanel();
        frame.addWindowListener(
                new WindowAdapter() {
                    public void windowClosing(WindowEvent e) {
                        System.exit(0);
                    }
                }
        );
        frame.getContentPane().add(panel,"Center");
        frame.setSize(panel.getPreferredSize());
        frame.setVisible(true);
    }
}

public class Main{
    static Socket socket;
    public static void main(String[] args) {
        MainPanel.launch();
    }

    static void writeCommand(int command, Socket soc) {
        // If no socket is null return
        if(soc==null)
            return;
        // if socket is connected send command
        if(soc.isConnected())
        {
            byte[] cmdByte=new byte[2];
            cmdByte[0]=(byte)command;
            byte[] temp;
            temp = "!".getBytes(StandardCharsets.US_ASCII);
            cmdByte[1]=temp[0];
            try {
                soc.getOutputStream().write(cmdByte);
            } catch (Exception e1) {
                e1.printStackTrace();
            }
        }
    }
}