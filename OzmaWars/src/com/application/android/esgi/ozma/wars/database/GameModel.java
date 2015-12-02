package com.application.android.esgi.ozma.wars.database;

public class GameModel {

	private int id;
	private int score;
	private int life;
	private int level;
	private int status;

	public GameModel() { }

	public static GameModel init(int _id, int _score, int _life, int _level, int _status) {
		GameModel game = new GameModel();
		game.setId(_id);
		game.setScore(_score);
		game.setLife(_life);
		game.setLevel(_level);
		game.setStatus(_status);

		return game;
	}

	public void setId(int _id) { this.id = _id; }
	public void setScore(int _score) { this.score = _score; }
	public void setLife(int _life) { this.life = _life; }
	public void setLevel(int _level) { this.level = _level; }
	public void setStatus(int _status) { this.status = _status; }
	
	public int getId() { return this.id; }
	public int getScore() { return this.score; }
	public int getLife() { return this.life; }
	public int getLevel() { return this.level; }
	public int getStatus() { return this.status; }
}