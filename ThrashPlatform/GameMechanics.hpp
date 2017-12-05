#pragma once

enum NPCState
{
	Idle,
	Moving,
	Attack,
	Chacing,
	Jump,
	Kill
};

struct NPCProperties
{
	int fraction;
	NPCState state;
	double range;
	double InteractionRange;
	double MaxSpeed;
	double Acceleration;
	double breakSpeed;
	double interactionColdDown;
	double hp;
	double maxhp;
	double damage;
	double armor;
};