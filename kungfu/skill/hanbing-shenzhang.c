// hanbing-shenzhang.c  寒冰神掌 6/25/2000 Modifed 
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "却见$N右掌一缩，竟以左手单掌抵御对方掌力，接着运寒冰真气于右手，伸出食中二指向$n$l戳去",
        "force" : 200,
        "dodge" : -10,
        "damage_type" : "刺伤",
        "parry" : 10,
        "lvl" : 1,
]),
([      "action" : "$N竖掌挡开$n，左掌加运内劲，向$p背心直击而下，这一掌居高临下，夹杂寒风，势道奇劲",
        "force" :300,
        "dodge" : 5,
        "parry" : -5,
        "damage_type" : "瘀伤",
        "lvl" : 50,
]),
([      "action" : "$N手腕一翻，左右两掌分别拍出，形态仿似太极拳的十字手，可随即跟来的却是两道阴冷的寒气",
        "force" : 350,
        "parry" : -15,
        "dodge" : 20,
        "damage_type" : "内伤",
        "lvl" : 100,
]),
([      "action" : "$N看似全然处于下风，双臂出招极短，攻不到一尺便即缩回，显似只守不攻，但突然右掌一伸，拍向$n",
        "parry" : 10,
        "force" : 420,
        "dodge" : -5,
        "damage_type" : "瘀伤",
        "lvl" : 150,
]),
([      "action" : "$N右手连指三指，逼得$n连退三步，接着无名指弹$p手腕，右手一抬，猛然按向$p$l，劲力阴冷狠辣",
        "force" : 450,
        "dodge" : -10,
        "damage_type" : "瘀伤",
        "lvl" : 180,
]),

});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
        if (!me->query("family") || me->query("family/master_id") != "zuo lengchan")
                return notify_fail("你只能从左冷禅那里学得寒冰神掌。\n");
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练寒冰神掌必须空手。\n");
        if ((int)me->query_skill("hanbing-zhenqi", 1) < 140)
                return notify_fail("你的寒冰真气火候不够，无法学寒冰神掌。\n");
        if ((int)me->query_skill("songyang-zhang", 1) < 140)
                return notify_fail("你的大嵩阳掌火候不够，无法学寒冰神掌。\n");
        if ((int)me->query("max_neili") < 2000)
                return notify_fail("你的内力太弱，无法练寒冰神掌。\n");
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
        level = (int)me->query_skill("hanbing-shenzhang", 1);
        if (me->query_temp("ss_feiwu") == 2){
            return([      
                   "action": HIW "紧接着$N"HIW"右手一放一收，在$n"HIW"还没有反应过来时飞身欺前，运起「寒冰真气」翻腕就是一掌」！"NOR,
                   "force" : 550,
                   "dodge" : 20,
                   "damage_type" : "瘀伤",
                   ]);
            }
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
//        if (lvl < 199 ) return 0;
        
        if ((int)me->query("jingli") < 70)
                return notify_fail("你的精力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练寒冰神掌。\n");
        me->receive_damage("jingli", 50);
        me->receive_damage("neili", 10);
        if(me->query_skill("hanbing-shenzhang", 1) > 160)
                me->receive_damage("jingli", 10);
        if(me->query_skill("hanbing-shenzhang", 1) > 190)
                me->receive_damage("neili", 5);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
     /*  if( random(me->query_skill("hanbing-shenzhang")) > 45) {
                  victim->apply_condition("cold_poison", random(3) + 2 +
                        victim->query_condition("cold_poison"));
        }
          */
       string msg;
        int lvl= me->query_skill("hanbing-shenzhang", 1);
        int j = (lvl - 100) / 5 + 1;
        if ( j > 6 ) j = 6;
        
        if(random(me->query_skill("hanbing-shenzhang", 1)) > 50
        && me->query("neili")>1000
        && random(me->query("neili"))>victim->query("neili")/4)
{
          if(victim->query("neili")/2 < me->query("neili"))
             victim->apply_condition("cold_poison", 2+victim->query_condition("cold_poison"));       
          else
             me->apply_condition("cold_poison", 1+victim->query_condition("cold_poison"));
        }
        if(random(me->query_con())>20
         && lvl >= 100
         && random(me->query_str())>20
         && me->query_skill_prepared("strike") == "hanbing-shenzhang"
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

string perform_action_file(string action)
{
        return __DIR__"hanbing-shenzhang/" + action;
}
