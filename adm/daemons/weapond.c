// weapond.c
// moved slash weapon and poison hit here.
// by snowman@SJ.
// Modified by snowman@SJ 01/05/2001

#include <ansi.h>
#include <combat.h>

mapping	weapon_actions = ([
	"slash": ([
		"damage_type":	"割伤",
		"action":		"$N挥动$w，斩向$n的$l",
		"parry":		20,
		]),
	"slice": ([
		"damage_type":	"劈伤",
		"action":		"$N用$w往$n的$l砍去",
		"dodge":		20,
		]),
	"chop":	([
		"damage_type":	"劈伤",
		"action":		"$N的$w朝着$n的$l劈将过去",
		"parry":		-20,
		]),
	"hack":	([
		"action":		"$N挥舞$w，对准$n的$l一阵乱砍",
		"damage_type":	"劈伤",
		"damage":		30,
		"dodge":		30,
		]),
	"thrust": ([
		"damage_type":	"刺伤",
		"action":		"$N用$w往$n的$l刺去",
		"dodge":		15,
		"parry":		-15,
		]),
	"pierce": ([
		"action":		"$N的$w往$n的$l狠狠地一捅",
		"damage_type":	"刺伤",
		"dodge":		-30,
		"parry":		-30,
		]),
	"whip":	([
		"action":		"$N将$w一扬，往$n的$l抽去",
		"damage_type":	"拉伤",
		"dodge":		-20,
		"parry":		30,
		]),
	"impale": ([
		"action":		"$N用$w往$n的$l直戳过去",
		"damage_type":	"刺伤",
		"dodge":		-10,
		"parry":		-10,
		]),
	"bash":	([
		"action":		"$N挥舞$w，往$n的$l用力一砸",
		"damage_type":	"砸伤",
		]),
	"crush": ([
		"action":		"$N高高举起$w，往$n的$l当头砸下",
		"damage_type":	"砸伤",
		]),
	"slam":	([
		"action":		"$N手握$w，眼露凶光，猛地对准$n的$l挥了过去",
		"damage_type":	"挫伤",
		]),
	"throw": ([
		"action":		"$N将$w对准$n的$l射了过去",
		"damage_type":	"刺伤",
		"post_action":	(: call_other, __FILE__, "throw_weapon"	:),
		]),
]);

varargs	mapping	query_action()
{
	string verb, *verbs;

	verbs =	previous_object()->query("verbs");

	if( !pointerp(verbs) ) return weapon_actions["hit"];
	else {
		verb = verbs[random(sizeof(verbs))];
		if( !undefinedp(weapon_actions[verb]) )	return weapon_actions[verb];
		else return weapon_actions["hit"];
	}	
}

void throw_weapon(object me, object victim, object weapon, int damage)
{
	if( objectp(weapon) ) {
		if( (int)weapon->query_amount()==1 ) {
			weapon->unequip();
			tell_object(me,	"\n你的" + weapon->query("name") + "用完了！\n");
		}
		weapon->add_amount(-1);
	}
}

function bash_weapon(object me,	object victim, object weapon, int damage)
{
	return (: call_other, __FILE__,	"weapon_cut", me, victim, weapon, damage :);

}


int weapon_cut(object me, object victim, object	weapon,	object vweapon,	int damage)
{	
	int wp,	wap, wdp;  
	string poison;
	
	if(!objectp(weapon) ) return 0;	

	// poisoned weapon hit.
	if (stringp(poison = weapon->query("poisoned"))	
	&& intp(wp = weapon->query("poison_number")) 
	&& random(10) >	5  
	&& wp >	1 
	&& victim->query_condition(poison) < 70) {     // upper	limit for poison hit.
		if (wp == 2)		       
			weapon->set_temp("apply/long", ({weapon->query("long")+"好象是被喂过剧毒，不过效果已经不明显了。\n"}));
		weapon->add("poison_number", -1);
		victim->apply_condition(poison,	 victim->query_condition(poison) + random(10));

		if(victim->query("race") == "人类" && !victim->query("mute"))
			message_vision(HIR"$N只觉得伤口上一麻，大叫一声：不好！\n"NOR,victim);

		else if(victim->query("race") == "人类")
			message_vision(HIR"$N只觉得伤口上一麻，眉头一挤，显然是发怒了！\n"NOR,victim);

		else  message_vision(HIR"$N猛然一颤，伤口处流出黑血，凶相毕露！\n"NOR,victim);

		if(!victim->is_killing(me->query("id"))) victim->kill_ob(me);
	}
	
	if( weapon->query("skill_type")	== "throwing" && damage	=! RESULT_PARRY){
		weapon = new(base_name(weapon));
		weapon->set_amount(1);
		weapon->move(environment(victim));
		return 0;
	}
	
	if( !objectp(vweapon)) return 0;
	
	if( vweapon->query("skill_type") == "throwing" ) return	0;
	// hoho..... by	snowman@SJ
	if( intp(wp = vweapon->query_temp("no_weapon_cut")) ){
		wp--;
		if( wp <= 0 )	wp = 0;
		vweapon->set_temp("no_weapon_cut", wp);
		return 0;
	}
	
	// slash_weapon	cut.
	if( weapon->query("flag") == 4)	{
		wp = weapon->query("sharpness")	+ weapon->query_temp("apply/sharpness");
		wap = vweapon->query("sharpness") + vweapon->query_temp("apply/sharpness");
		wdp = vweapon->query("rigidity") + vweapon->query_temp("apply/rigidity");
		if( wp > 10 ) wp = 10;
		if( wap	> 10 ) wap = 10;
		if( wdp	> 10 ) wdp = 10;
		if( wp > 0 && wp > wap && wp > wdp && 
		((random(me->query("str")) > victim->query("str")/2 && damage =	RESULT_PARRY)
		|| (random(me->query("str")) > victim->query("str")/3 && damage	> 0))){
			message_vision(WHT "只听见「哐」地一声轻响，$N手中的"+vweapon->name()+WHT"已经被"+weapon->name()+WHT"削为两截！\n"NOR, victim );
			vweapon->broken("断掉的");
		} 
		return 1;
	}
	     
	// bash_weapon break.
	else if( random(100) > 60 
		&& damage = RESULT_PARRY 
		&& weapon->query("skill_type") != "whip"
		&& vweapon->query("special") !=	"nobreak"
		&& vweapon->query("material") != "softsteel" 
		&& vweapon->query("skill_type")	!= "whip" 
		&& vweapon->query("rigidity") <= weapon->query("rigidity")) {	
			wap = ((int)weapon->query("rigidity")+weapon->query_temp("apply/rigidity")) * 5;
			wdp = ((int)vweapon->query("rigidity")+vweapon->query_temp("apply/rigidity")) *	5;	       

			wap *= weapon->query_amount() >	1?weapon->query_amount():1;
			wap *= (int)weapon->query("base_weight") / 500 + (int)me->query("str");
		      
			wdp *= vweapon->query_amount() > 1?vweapon->query_amount():1;
			wdp *= (int)vweapon->query("base_weight") / 500	+ (int)victim->query("str");
		      
			wap = random(wap);	    
			if( wap	> 2 * wdp) {
				message_vision(HIW "$N只觉得手中" + vweapon->name() + "把持不定，脱手飞出！\n" NOR,victim);
				vweapon->unequip();
				vweapon->move(environment(victim));
				victim->reset_action();
			} 
			else if( wap > wdp ) {
				message_vision(HIW "只听见「啪」地一声，$N手中的"+vweapon->name()+"已经断为两截！\n" NOR, victim );
				vweapon->broken("断掉的");
			}   
			else if( wap > wdp / 2 && random(2)) 
				message_vision("$N只觉得手中" +	vweapon->name()	+ "一震，险些脱手！\n",victim);
		      
			else if( random(3) == 1) message_vision("$N的" + weapon->name()	+ "和$n的" + vweapon->name()+"相击，冒出点点的火星。\n", me, victim);
			return 1;
	}
	
	return 0;
}
