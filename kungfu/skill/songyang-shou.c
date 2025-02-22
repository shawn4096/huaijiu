// songyang-shou.c  嵩阳手
// Created by Numa 2000.1.5
// Modified by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N一掌高，一掌低，摆出了“嵩阳手”的起首式--「嵩阳拜首」",
        "force" : 160,
        "dodge" : 10,
        "damage_type" : "瘀伤",
        "lvl" : 0,
        "skill_name" : "嵩阳拜首"
]),
([      "action" : "$N左掌一提，右掌一招便即劈出。但见他一掌出手，登时全身犹如渊停岳峙，气度凝重",
        "force" : 230,
        "dodge" : 5,
        "damage_type" : "内伤",
        "lvl" : 30,
        "skill_name" : "渊停岳峙"
]),
([      "action" : "$N大喝一声道：“小心了！”随即双掌凌空推出，一股猛烈的掌风向着$n逼体而至",
        "force" : 290,
        "dodge" : 5,
        "damage_type" : "瘀伤",
        "lvl" : 60,
        "skill_name" : "中岳迎风"
]),
([      "action" : "$N两手连续挥舞，双掌交错，一拍$n的面门，一拍$n的小腹",
        "force" : 340,
        "dodge" : 10,
        "damage_type" : "瘀伤",
        "lvl" : 80,
        "skill_name" : "松柏苍天",
]),
([      "action" : "$N踏前一步，绕$n坻壁而行，双手快如风、迅如电，不停击向$n周身各大要穴",
        "force" : 380,
        "dodge" : 15,
        "lvl" : 100,
        "damage_type" : "瘀伤",
        "skill_name" : "坻壁而行"
]),
([      "action" : "$N运气丹田，连续几个斜步围绕$n周身不断出掌，其迅捷令$n全身各大要穴均暴露无疑",
        "force" : 400,
        "dodge" : 5,
        "damage_type" : "内伤",
        "lvl" : 120,
        "skill_name" : "岳雾缭人"
]),
([      "action" : "$N蹂身向前，身行猛的一窜，窜至半空又两手互抵，双掌竖直向$n的天门压去",
        "force" : 410,
        "dodge" : 10,
        "damage_type" : "内伤",
        "lvl" : 140,
        "skill_name" : "临渊下探"
]),
});

int valid_enable(string usage) { return usage=="hand" ||  usage=="parry"; }

/*
int valid_combine(string combo) 
{
        object me = this_player(); 

        if ((int)me->query_skill("songyang-zhang") > 100
        &&  (int)me->query_skill("songyang-shou") > 100)
                return combo=="songyang-shou";
        return notify_fail("你的大嵩阳神掌和嵩阳手的火候不够。\n");
}
*/

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("学习嵩阳手必须空手。\n");
        if ((int)me->query_skill("hanbing-zhenqi", 1) < 20)
                return notify_fail("你的寒冰真气火候不够，无法学嵩阳手。\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力太弱，无法练嵩阳手。\n");
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
        level = (int)me->query_skill("songyang-shou", 1);
        
        if (me->query_temp("ss_yinyang") == 1 && random(me->query_skill("songyang-zhou",1)/10)>12)
        {
                switch(random(2))
                {
                        case(0) :
                                return([
                                        "action": HIW "$N"HIW"倏地欺近身来，远远发出一掌，掌力击在$n"HIW"胸口，此掌寒气逼人，$n"HIW"立时一个哆嗦！"NOR,
                                        "force" : 480,
                                        "dodge" : -10,
                                        "damage_type" : "瘀伤",
                                        ]);
                                break;
                        case(1) :
                                return([
                                        "action": HIW "$N"HIW"倏地欺近身来，远远发出一掌，掌力击在$n"HIW"胸口，此掌炙热无比，$n"HIW"浑身顿感难受！"NOR,
                                        "force" : 480,
                                        "dodge" : 10,
                                        "damage_type" : "瘀伤",
                                        ]);
                                break;
                }
        }
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}


mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        string msg;
        int focus = me->query_temp("ss/focus");
        int lvl= me->query_skill("songyang-shou", 1);
        int j = (lvl - 100) / 5 + 1;

        if (me->query_temp("ss/hb") && !victim->is_busy()) {
            victim->apply_condition("cold_poison", victim->query_condition("cold_poison")*120/100 + focus);
            victim->start_busy(2);
            victim->add("neili",-me->query_skill("force"));
            if (victim->query("neili") < 0) victim->set("neili",0);
            msg = HIW"$n被$N这一掌击中，陡然一哆嗦，似乎全身的血液即将冻结一般！\n"NOR;
            message_vision(msg, me, victim);
        }
        if ( j > 6 ) j = 6;
        
        if(random(me->query_con())>20
         && lvl >= 100
         && random(me->query_str())>20
         && me->query_skill_prepared("hand") == "songyang-shou"
         && me->query("neili") > 1000
         && me->query("max_neili") > 1500 
         && me->query("jiali")){
           me->add("neili", -50);
   switch(random(7)){
            case 0 :
               msg = HIB"$N运起寒冰真气，脸上升起一鼓若隐若现的白气，使出寒冰神掌中的「"HIW"天寒地冻 "HIB"」，双掌一股刚猛之力向$n击去。\n"NOR;
               victim->apply_condition("cold_poison", j + victim->query_condition("cold-poison"));
               break;  
            case 1 :
               msg =HIB"$N运起寒冰真气，脸上升起一鼓若隐若现的白气，左掌再使出寒冰神掌中的「"HIW"寒风刺骨"HIB"」，单掌飘忽不定，$n顿时感觉一股阴森之气迎面而来。\n"NOR;
               victim->receive_damage("jing", lvl);
               victim->receive_wound("jing", lvl);
               break;
            case 2 :
               msg =HIB"$N右掌接着使出寒冰神掌中的「"HIW"冰天雪地"HIB"」，单掌变的雪白，向$n击去。\n"NOR;
               victim->add("jingli",-lvl);
               break;
            case 3 :
               msg =HIB"$N运起寒冰真气，脸上升起一鼓若隐若现的白气，使出寒冰神掌中的「"HIW"飞雪连天"HIB"」，双掌变的雪白，打出一股寒天澈地之气！向$n击去。\n"NOR;
               victim->add("neili", -lvl*3);
               if( victim->query("neili") < 0) 
                victim->set("neili", 0);
               break;
            case 4 :
               msg =HIB"$N凝神定气，使出寒冰神掌中的「"HIW"千里冰封"HIB"」，双掌势如雷霆，将力一股阴寒之气直向$n送去。\n"NOR;
               victim->start_busy(2 + random(2));
               break;
            case 5:
               msg =HIB"$N深深吸了口气，使出寒冰神掌中的「"HIW"万里雪飘"HIB"」，向$n送出一股奇寒无比的真力。\n"NOR;
               victim->receive_damage("qi", lvl*3);
               victim->receive_wound("qi", lvl*3);
               break;
            case 6:
               msg =HIB"$N运起寒冰真气，脸上升起一鼓若隐若现的白气，使出寒冰神掌之精髓「万寒归一」，左右双掌连续击出，如同鬼魅，打向$n。\n"NOR;
                victim->apply_condition("no_perform", 1);
               break;
           }   
           if (me->query_temp("ss_feiwu"))
                  victim->apply_condition("cold_poison", 30 +
                        victim->query_condition("cold_poison"));      
           msg +=HIW"$n只觉得$N这一掌夹着奇寒无比的真气，变幻百端，势如破竹般，注入全身穴道, 不能动弹。\n"NOR;
           message_vision(msg, me, victim);
        } 
}

int practice_skill(object me)
{
       
        if ((int)me->query("jingli") < 50)
                return notify_fail("你的精力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练嵩阳手。\n");
        me->receive_damage("jingli", 30);
        me->receive_damage("neili", 5);
        if(me->query_skill("songyang-shou", 1) > 170)
                me->receive_damage("jingli", 10);
        if(me->query_skill("songyang-shou", 1) > 190)
                me->receive_damage("neili", 5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"songyang-shou/" + action;
}

