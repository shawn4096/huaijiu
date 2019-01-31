// sanhua-zhang.c -É¢»¨ÕÆ
inherit SKILL;
#include <ansi.h>
mapping *action = ({
([	"action" : "$NºÏÕÆ±§Çò£¬Ò»Ê½¡¸"HIG"´ºÉî·¼²Ý¾¡"NOR"¡¹£¬Ë«ÕÆ±ä»ÃÍÌÍÂ£¬»º»ºÍÆÏò$nµÄ$l",
    "force" : 180,
        "dodge" : 5,
        "parry" : 5,
	"lvl" : 0,
	"skill_name" : "´ºÉî·¼²Ý¾¡",
        "damage_type" : "ðöÉË"
]),
([	"action" : "$NÎåÖ¸ÕÀ¿ª£¬Ò»Ê½¡¸"GRN"ÏÄÏÐ¶ÀÀ¼Ü°"NOR"¡¹£¬×óÓÒÕÆ´©²å·­·É£¬¼²Ïò$nµÄ$lÅÄÈ¥",
    "force" : 250,
        "dodge" : 10,
        "parry" : 5,
    "lvl" : 30,
	"skill_name" : "ÏÄÏÐ¶ÀÀ¼Ü°",
        "damage_type" : "ðöÉË"
]),
([	"action" : "$NÊ¹Ò»Ê½¡¸"HIY"Çïº¨¾ÕËªÇå"NOR"¡¹£¬×óÕÆÐéÍÐ£¬ÓÒÕÆÕ§ÉìÕ§ºÏ£¬ÃÍµØ²åÍù$nµÄ$l",
    "force" : 320,
        "dodge" : -5,
        "parry" : 5,
    "lvl" : 60,
	"skill_name" : "Çïº¨¾ÕËªÇå",
        "damage_type" : "ðöÉË"
]),
([	"action" : "$NË«ÕÆÑªºì£¬Ò»Ê½¡¸"HIW"¶¬ÎÔÌýÃ·Ò÷"NOR"¡¹£¬»Ã³ÉÂþÌìÃ·»¨¶ä¶ä£¬Óêµã°ãÏò$n»÷È¥",
    "force" : 380,
        "dodge" : 10,
        "parry" : 5,
    "lvl" : 90,
	"skill_name" : "¶¬ÎÔÌýÃ·Ò÷",
        "damage_type" : "ðöÉË"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_combine(string combo) 
{
        object me;
        me = this_player(); 
        if ((int)me->query_int() > 40)
                return combo=="nianhua-zhi"; 
}


int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("Á·É¢»¨ÕÆ±ØÐë¿ÕÊÖ¡£\n");
	if ((int)me->query_skill("yijin-jing", 1) < 20)
		return notify_fail("ÄãµÄÒ×½î¾­ÄÚ¹¦»ðºò²»¹»£¬ÎÞ·¨Ñ§É¢»¨ÕÆ¡£\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("ÄãµÄÄÚÁ¦Ì«Èõ£¬ÎÞ·¨Á·É¢»¨ÕÆ¡£\n");
	return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
	level   = (int) me->query_skill("sanhua-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("ÄãµÄÌåÁ¦Ì«µÍÁË¡£\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("ÄãµÄÄÚÁ¦²»¹»Á·É¢»¨ÕÆ¡£\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
        return __DIR__"sanhua-zhang/" + action;
}
