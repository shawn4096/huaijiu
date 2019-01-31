//¶Î¼Ò½£·¨
//cool@SJ,990528
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
        "action" : "$N×óÊÖÄóÁË¸ö½£¾÷£¬ÓÒÊÖ$wÆ½Æ½µÝ³ö£¬Ò»Ê½¡¸ÆäÀû¶Ï½ð¡¹Ö±´Ì$nµÄÇ°ÐØ",
        "damage_type" : "´ÌÉË"
]),
([
        "action" : "$N×ÝÉíÏòÇ°£¬$w´ÓÒ»¸öÏë²»µ½µÄ½Ç¶ÈÍ»È»µ¯³ö£¬Ò»Ê½¡¸±Ì¼¦±¨Ïþ¡¹Ö±´Ì$nµÄ×óÀß",
        "damage_type" : "´ÌÉË"
]),
([
        "action" : "$NÒ»ÕÐ¡¸½ðÂíÌÚ¿Õ¡¹£¬ÉíÐÎÔ¾ÔÚ°ë¿Õ£¬$wºáÏ÷¶ø³ö£ £¬Ö±Ïò$nµÄÍ·²¿",
        "damage_type" : "´ÌÉË"
]),
([
        "action" : "$N½£ÉíÐ±»Ó£¬½£¼âÖ¸Ïò$nµÄ¸¹²¿£¬Ò»ÕÐ¡¸±ÌÔ¨ÌÚòÔ¡¹£¬×ÔÏÂ¶øÉÏ£¬ÆÊÏò$n",
        "damage_type" : "´ÌÉË"
]),
([
         "action" : "$NË«½ÅÀëµØ£¬Ð±·É¶ø³ö£¬$wÉäÏò$nµÄ$l,ºÃÒ»ÕÐ¡¸Ð¦Ö¸ÌìÄÏ¡¹",
         "damage_type" : "´ÌÉË"
]),
([ 
        "action" : "$N³¤Ð¥Ò»Éù£¬ºá½£Çá»ÓÒþÒþÍ¸³öÍõµÀÖ®Òâ£¬ÕýÊÇ¶Î¼Ò²»´«Ö®ÃØ¡¸ÖðÂ¹ÖÐÔ­¡¹£¬½£·çÕÖ×¡$nµÄÈ«Éí",
        "damage_type" : "´ÌÉË"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
            return notify_fail("ÄãµÄÄÚÁ¦²»¹»¡£\n");
        if ((int)me->query_skill("qiantian-yiyang", 1) < 20)
            return notify_fail("ÄãµÄÇ¬ÌìÒ»Ñô»ðºòÌ«Ç³¡£\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i,level;
		string msg;
        level   = (int) me->query_skill("duanjia-jianfa",1);
        if (level > 200) level = 200 + (level- 200)/10;
      
	     if(me->query_temp("fenglei")){
          switch(me->query_temp("fenglei")){
           case 4: msg = HIW"$NÊ©Õ¹³ö£¢ÌìÁúÏè£¢£¬Ò»´ó²½Ô¾ÆðÔÚ¿ÕÖÐ£¬ÉíÌåÎ§ÈÆ×Å$n²»Í£Ðý×ª£¬Á¬ÐøÓÉËÄ¸ö·½Î»Ïò$n´Ì³öËÄ½££¬¿ì½ÝÎÞ±È£®\n" NOR;break;
			 case 3: msg = HIW"$N½è×Å$nµÄ¾¢·çÔÚ¿ÕÖÐÒ»µ´£¬Ë«ÊÖÎÕ½££¬Ò»½£´Ì³ö£¬ÓÌÈçÓ¥»÷³¤¿Õ£¬£¢ÎË£¢µÄÒ»Éù£¬½£¹âÏóÒ»µÀÉÁµç°ã´ÌÏò$n£®\n" NOR;break;
             case 2: msg = HIW"$N×óÕÆ»òÅÄ»òÅü£¬ÎüÒý$nµÄ×¢Òâ£¬ÓÒÊÖ½£×ªÎÞÐÎ£¬»®³öÊýµÀ½£Æø£¬½ô½Ó×ÅÒ»½£ºáÅÄ£¬ÎÞÊý½£·çÏ®Ïò$nµÄÈ«Éí£®\n" NOR; break;
			 case 1: msg = HIW"$NÉíÌåÏÂ³Á£¬Í»È»×óÊÖÒ»ÕÆÏòµØÅÄ³ö£¬Í·ÏÂ½ÅÉÏ£¬Éí×Ó½è×ÅÕÆÁ¦Ïò¿ÕÖÐÒ»Æ®£¬ÓÖÊÇ¿ìËÙÎÞ±ÈµÄ´Ì³öÁ½½££¬Ö±Ïò$n£®\n"NOR;break;
             default: msg = HIW"$NÉíÌåÏÂ³Á£¬Í»È»×óÊÖÒ»ÕÆÏòµØÅÄ³ö£¬Í·ÏÂ½ÅÉÏ£¬Éí×Ó½è×ÅÕÆÁ¦Ïò¿ÕÖÐÒ»Æ®£¬ÓÖÊÇ¿ìËÙÎÞ±ÈµÄ´Ì³öÁ½½££¬Ö±Ïò$n£®\n" NOR; break;
          }
             me->add_temp("fenglei", -1);
              return ([
                "action":msg,
                "damage":150+random(50), 
                "damage_type":"´ÌÉË",
                "dodge": random(15)+15, 
                "force": random(50)+level/2+200,
                "parry": 5+random(5),
                "skill_name" : "ÁøÐõ½£·¨",
              ]);
        }
		
	for(i = sizeof(action); i > 0; i--) {
            if(level > action[i-1]["lvl"]) {
               return ([
                "action":action[NewRandom(i, 20, level/5)]["action"],
                "damage":random(80)+80,
                "damage_type": action[NewRandom(i, 20, level/5)]["damage_type"],
                "dodge": random(15),
                "force": 150+random(200),
                "parry": 20+random(10),
               ]);
            }
        }
}

int practice_skill(object me)
{
        object weapon;
        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
                return notify_fail("ÄãÊ¹ÓÃµÄÎäÆ÷²»¶Ô¡£\n");
        if ((int)me->query("jingli") < 40)
                return notify_fail("ÄãµÄÌåÁ¦²»¹»Á·¶Î¼Ò½£·¨¡£\n");
        if((int)me->query("neili") < 30)
                return notify_fail("ÄãµÄÄÚÁ¦²»¹»Á·¶Î¼Ò½£·¨¡£\n");
        me->receive_damage("jingli", 15);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"duanjia-jianfa/" + action;
}
