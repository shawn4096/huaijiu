// skill.c
// From ES2
// Modified by Yu Jue for JY (07/18/98)
// Modified by snowman@SJ 07/04/2001
// added string query_sk_mapped(string skill)

#include <ansi.h>
#include <dbase.h>

mapping skills;
mapping learned;
mapping skill_map;
mapping skill_prepare;

mapping query_skills() { return skills; }
mapping query_learned() { return learned; }

void set_skill(string skill, int val)
{
	if( !find_object(SKILL_D(skill))
	&&      file_size(SKILL_D(skill)+".c") < 0 )
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) ) skills = ([ skill: val ]);
	else skills[skill] = val;
}

int delete_skill(string skill)
{
	if( mapp(skills) ) {
		map_delete(skills, skill);
		if( mapp(learned) ) {
			map_delete(learned, skill);
			return undefinedp(learned[skill]);
		}
		return undefinedp(skills[skill]);
	}
	return 0;
}

// This function 'map' a skill <skill> to another skill <mapped_to>.
// If 2nd argument not given, cancel the mapped skill <skill>.
varargs void map_skill(string skill, string mapped_to)
{
	if( !mapped_to && mapp(skill_map) ) {
		map_delete(skill_map, skill);
		return;
	}

	if( !find_object(SKILL_D(skill))
	&&      file_size(SKILL_D(skill)+".c") < 0 )
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) || undefinedp(skills[mapped_to]) )
		return;
		
	if( !mapp(skill_map) ) skill_map = ([ skill: mapped_to ]);
	else skill_map[skill] = mapped_to;
}

// This function 'prepare' a skill <skill> to another skill <mapped_to>.
// If 2nd argument not given, cancel the prepared skill <skill>.
varargs void prepare_skill(string skill, string mapped_to)
{
	if( !mapped_to && mapp(skill_prepare) ) {
		map_delete(skill_prepare, skill);
		return;
	}

	if( !find_object(SKILL_D(skill))
	&&      file_size(SKILL_D(skill)+".c") < 0 )
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) || undefinedp(skills[mapped_to]) )
		return;
		
	if( !mapp(skill_prepare) ) skill_prepare = ([ skill: mapped_to ]);
	else skill_prepare[skill] = mapped_to;
}

string query_skill_mapped(string skill)
{
	if( mapp(skill_map) && !undefinedp(skill_map[skill]) )
		return skill_map[skill];
	return 0;
}

string query_skill_prepared(string skill)
{
	if( mapp(skill_prepare) && !undefinedp(skill_prepare[skill]) )
		return skill_prepare[skill];
	return 0;
}

string query_sk_mapped(string skill)
{
	string *sk;
	int i;
	
	if( !mapp(skill_map) || !skill || !stringp(skill) ) return 0;
	sk = keys(skill_map);
	
	for(i = 0; i<sizeof(sk); i++) 
		if( skill_map[sk[i]] == skill ) return sk[i];
	return 0;
}

varargs int query_skill(string skill, int raw)
{
	if( !raw ) {
		int s;
		
		s = query_temp("apply/" + skill);
		if( mapp(skills) ) {
			s += skills[skill] / 2;
			if( mapp(skill_map) )
				s += skills[skill_map[skill]];
		}
		return s;
	}
	if( mapp(skills) && !undefinedp(skills[skill]) ) return skills[skill];
	return 0;
}

mapping query_skill_map()
{
	return skill_map;
}

mapping query_skill_prepare()
{
	return skill_prepare;
}

int skill_death_penalty()
{
	string *sk;
	int i, j;

	if( !mapp(skills) ) return 0;

	sk = keys(skills);
	
	if (!mapp(learned)) learned = ([ ]);
	for(i = 0; i<sizeof(sk); i++) {
		j = skills[sk[i]] + 1;
		learned[sk[i]] -= (j*j+1)/2;
		if (learned[sk[i]] < 0) {
			learned[sk[i]] += (j*j+1)/2;
			j = skills[sk[i]]--;
			learned[sk[i]] += (j*j+1)/2;
		}
		if (j <= 1) {
			map_delete(skills,sk[i]);
			map_delete(learned,sk[i]);
		}
	}
	skill_map = 0;
	skill_prepare = 0;
	return 1;
}

varargs void improve_skill(string skill, int amount, int weak_mode)
{
	int spi = 30;
	int lvl = 0;

	if (!userp(this_object())) return;
	if( !find_object(SKILL_D(skill))
	&&      file_size(SKILL_D(skill)+".c") < 0 )
		error("F_SKILL: No such skill (" + skill + ")\n");

	if (mapp(skills) && SKILL_D(skill)->type() == "martial") {
		lvl = skills[skill];
		if (lvl*lvl*lvl/10 > this_object()->query("combat_exp")) weak_mode = 2;
	}

	if( !mapp(skills) ) skills = ([]);
	if( !weak_mode )
		if (undefinedp(skills[skill]))
			skills[skill] = 0;

	// Give learning penalty to those learning too much skills.
	if( sizeof(skills) > spi )
		amount /= sizeof(skills) - spi;

	if (amount < 1) amount = 1;

	if( !mapp(learned) ) learned = ([ skill : amount ]);
	else (int)learned[skill] += amount;

	if (learned[skill] > (spi = (skills[skill] + 1) * (skills[skill] + 1))) {
		learned[skill] = spi;
		if (weak_mode > 1) {
			if (!random(5)) tell_object(this_object(),
				HIY "����ʵս���鲻�㣬�谭����ġ�" + to_chinese(skill) + "��������\n" NOR);
		} else if (!weak_mode) {
			skills[skill]++;
			learned[skill] = 0;
			tell_object(this_object(), HIC "��ġ�" + to_chinese(skill) + "�������ˣ�\n" NOR);
			SKILL_D(skill)->skill_improved(this_object());
		}
	}
}
