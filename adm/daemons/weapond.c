// weapond.c
// moved slash weapon and poison hit here.
// by snowman@SJ.
// Modified by snowman@SJ 01/05/2001

#include <ansi.h>
#include <combat.h>

mapping	weapon_actions = ([
	"slash": ([
		"damage_type":	"����",
		"action":		"$N�Ӷ�$w��ն��$n��$l",
		"parry":		20,
		]),
	"slice": ([
		"damage_type":	"����",
		"action":		"$N��$w��$n��$l��ȥ",
		"dodge":		20,
		]),
	"chop":	([
		"damage_type":	"����",
		"action":		"$N��$w����$n��$l������ȥ",
		"parry":		-20,
		]),
	"hack":	([
		"action":		"$N����$w����׼$n��$lһ���ҿ�",
		"damage_type":	"����",
		"damage":		30,
		"dodge":		30,
		]),
	"thrust": ([
		"damage_type":	"����",
		"action":		"$N��$w��$n��$l��ȥ",
		"dodge":		15,
		"parry":		-15,
		]),
	"pierce": ([
		"action":		"$N��$w��$n��$l�ݺݵ�һͱ",
		"damage_type":	"����",
		"dodge":		-30,
		"parry":		-30,
		]),
	"whip":	([
		"action":		"$N��$wһ���$n��$l��ȥ",
		"damage_type":	"����",
		"dodge":		-20,
		"parry":		30,
		]),
	"impale": ([
		"action":		"$N��$w��$n��$lֱ����ȥ",
		"damage_type":	"����",
		"dodge":		-10,
		"parry":		-10,
		]),
	"bash":	([
		"action":		"$N����$w����$n��$l����һ��",
		"damage_type":	"����",
		]),
	"crush": ([
		"action":		"$N�߸߾���$w����$n��$l��ͷ����",
		"damage_type":	"����",
		]),
	"slam":	([
		"action":		"$N����$w����¶�׹⣬�͵ض�׼$n��$l���˹�ȥ",
		"damage_type":	"����",
		]),
	"throw": ([
		"action":		"$N��$w��׼$n��$l���˹�ȥ",
		"damage_type":	"����",
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
			tell_object(me,	"\n���" + weapon->query("name") + "�����ˣ�\n");
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
			weapon->set_temp("apply/long", ({weapon->query("long")+"�����Ǳ�ι���綾������Ч���Ѿ��������ˡ�\n"}));
		weapon->add("poison_number", -1);
		victim->apply_condition(poison,	 victim->query_condition(poison) + random(10));

		if(victim->query("race") == "����" && !victim->query("mute"))
			message_vision(HIR"$Nֻ�����˿���һ�飬���һ�������ã�\n"NOR,victim);

		else if(victim->query("race") == "����")
			message_vision(HIR"$Nֻ�����˿���һ�飬üͷһ������Ȼ�Ƿ�ŭ�ˣ�\n"NOR,victim);

		else  message_vision(HIR"$N��Ȼһ�����˿ڴ�������Ѫ�������¶��\n"NOR,victim);

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
			message_vision(WHT "ֻ�������ѡ���һ�����죬$N���е�"+vweapon->name()+WHT"�Ѿ���"+weapon->name()+WHT"��Ϊ���أ�\n"NOR, victim );
			vweapon->broken("�ϵ���");
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
				message_vision(HIW "$Nֻ��������" + vweapon->name() + "�ѳֲ��������ַɳ���\n" NOR,victim);
				vweapon->unequip();
				vweapon->move(environment(victim));
				victim->reset_action();
			} 
			else if( wap > wdp ) {
				message_vision(HIW "ֻ������ž����һ����$N���е�"+vweapon->name()+"�Ѿ���Ϊ���أ�\n" NOR, victim );
				vweapon->broken("�ϵ���");
			}   
			else if( wap > wdp / 2 && random(2)) 
				message_vision("$Nֻ��������" +	vweapon->name()	+ "һ����Щ���֣�\n",victim);
		      
			else if( random(3) == 1) message_vision("$N��" + weapon->name()	+ "��$n��" + vweapon->name()+"�����ð�����Ļ��ǡ�\n", me, victim);
			return 1;
	}
	
	return 0;
}
