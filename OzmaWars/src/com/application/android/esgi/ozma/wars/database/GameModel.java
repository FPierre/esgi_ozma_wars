package com.application.android.esgi.ozma.wars.database;

public class GameModel {

	private int id;
	private int score;
	private int life;
	private int level;
	private boolean state;

	public void setId(int _id) { this.id = _id; }
	public void setScore(int _score) { this.score = _score; }
	public void setLife(int _life) { this.life = _life; }
	public void setLevel(int _level) { this.level = _level; }
	public void setStatus(int _state) { this.state = (_state == 1) ? true : false; }
	
	public int getId() { return this.id; }
	public int getScore() { return this.score; }
	public int getLife() { return this.life; }
	public int getLevel() { return this.level; }
	public int getStatus() { return (state) ? 1 : 0; }
}