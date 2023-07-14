#include "DamageMessage.h"
#include "Entity/Entity.h"
#include "Common.h"

MyGame::DamageMessage* MyGame::DamageMessage::calculateDamage(Entity* attacker, Entity* victim, Power power, float criteRate)
{
	DamageMessage* dameMessage = new DamageMessage();
	int attack, defVictim, defLast, levelAttacker;
	float resElement, bnsElement, defFactor, critDMG;


	attack = attacker->getEntityStatByID(Stat::ATK)->getFinalValue();
	resElement = CONVERT_TO_PERCENT(victim->getEntityStatByID(power.convertIDResElement())->getFinalValue()) * 0.01f;
	bnsElement = CONVERT_TO_PERCENT(attacker->getEntityStatByID(power.convertIDBnsElement())->getFinalValue()) * 0.01f;
	levelAttacker = attacker->getLevel();

	defVictim = victim->getEntityStatByID(Stat::DEF)->getFinalValue();
	defFactor = 1.0f - ((float)defVictim / (float)(defVictim + 2 * levelAttacker + 100));

	defLast = defVictim * defFactor;

	dameMessage->_amount = (attack * (1.0f + CONVERT_TO_PERCENT(power.getPowerValue()) ) + power.getPowerNumber()) * (1.0f - resElement) * (1.0f + bnsElement) - defLast;

	// Crit DMG
	float ran = RandomHelper::random_real(0.0f, 1.0f);
	bool crit = (ran < criteRate * 0.01f);
	if (crit)
	{
		critDMG = CONVERT_TO_PERCENT(attacker->getEntityStatByID(Stat::CritDMG)->getFinalValue()) * 0.01f;
		dameMessage->_amount = dameMessage->_amount * (1.0f + critDMG);
	}

	dameMessage->_elementType = power.getElemType();
	dameMessage->_isCrit = crit;

	return dameMessage;
}
