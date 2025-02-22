// yunu-jiafa 玉女素心剑
// by xdd and shang 97/6
// Modify By River 98/10
inherit SKILL;
#include <ansi.h>
mapping *action = ({
([      "action" : "$N击高而下，一式「雁行斜击」，腾身下击，剑尖直点$n的$l",
        "force" : 130,
        "dodge" : 50,
        "damage" : 40,
        "parry" : 15,
        "lvl" : 0,
        "skill_name" : "雁行斜击",
        "damage_type" : "刺伤"
]),
([      "action" : "$N踏前数步，左手遥指，右手$w使一式「浪迹天涯」直劈$n的$l",
        "force" : 155,
        "dodge" : 45,
        "damage" : 65,
        "parry" : 20,
        "lvl" : 10,
        "skill_name" : "浪迹天涯",
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「花前月下」，$w颤动如鲜花招展风中，来回挥削$n的$l",
        "force" : 200,
        "dodge" : 40,
        "damage" : 80,
        "parry" : 10,
        "lvl" : 20,
        "skill_name" : "花前月下",
        "damage_type" : "刺伤"
]),
([      "action" : "$N剑尖上翻，指向自己的樱唇，一招「清饮小酌」，宛若举杯自饮一般，横扫$n的$l",
        "force" : 235,
        "dodge" : 35,
        "damage" : 85,
        "parry" : 15,
        "lvl" : 30,
        "skill_name" : "清饮小酌",
        "damage_type" : "刺伤"
]),
([      "action" : "$N使出「抚琴按箫」，$w自横脐前，做抚琴状，随即剑出中宫，平削$n的$l",
        "force" : 260,
        "dodge" : 30,
        "damage" : 90,
        "parry" : 5,
        "lvl" : 40,
        "skill_name" : "抚琴按箫",
        "damage_type" : "刺伤"
]),
([      "action" : "$N右手一招「彩笔画眉」，构成帘下梳妆之状，一脸娇羞，$w却未有停留，逼向$n的$l",
        "force" : 275,
        "dodge" : 25,
        "damage" : 95,
        "parry" : 20,
        "lvl" : 50,
        "skill_name" : "彩笔画眉",
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「举案齐眉」，双手齐握剑柄，举剑上挑，直划$n的$l",
        "force" : 290,
        "dodge" : 20,
        "damage" : 100,
        "parry" : 25,
        "lvl" : 70,
        "skill_name" : "举案齐眉",
        "damage_type" : "刺伤"
]),
([      "action" : "$N向前急进两步，一招「木兰回射」，蓦地里挺剑反手向背后刺出，直刺$n的$l",
        "force" : 305,
        "dodge" : 15,
        "damage" : 105,
        "parry" : 20,
        "lvl" : 90,
        "skill_name" : "木兰回射",
        "damage_type" : "刺伤"
]),
([  "action" : "$N一招「分花拂柳」，$w似左实右，似右实左，虚实莫辩，点向$n的喉头",
        "force" : 350,
        "dodge" : 10,
        "damage" : 110,
        "parry" : 15,
        "lvl" : 110,
        "skill_name" : "分花拂柳",
        "damage_type" : "刺伤"
]),
([  "action" : "$N眼角尽是笑意，眉目含情，一招「如影相随」，影随$n周身，身形飘飘中剑光熠熠生辉，",
        "force" : 375,
        "dodge" : 15,
        "damage" : 120,
        "parry" : 20,
        "lvl" : 130,
        "skill_name" : "如影相随",
        "damage_type" : "刺伤"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("yunu-xinjing", 1) < 20)
                return notify_fail("你的玉女心经功力不够。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
 
        int i, j, level;
        object target;             
        level   = (int) me->query_skill("yunu-jianfa",1);
        for(i = sizeof(action); i > 0; i--){
                if(level > action[i-1]["lvl"]){
                  j = NewRandom(i, 20, level/5);
                  target = offensive_target(me);    
                  if ( me->query_temp("hebi")
                    && me->query("jiali")
                    && random(10) > 5 ){ 
                  return ([  
                           "action" :random(2)? HIC+action[j]["action"]+NOR :HIR+action[j]["action"]+NOR,
                           "force" : action[j]["force"]+60,
                           "dodge": action[j]["dodge"]+15,
                           "damage": action[j]["damge"]+level/4,
                           "lvl" : action[j]["lvl"],
                           "parry":action[j]["parry"]+ 20,
                           "weapon" : random(2)?"剑气":"剑锋",
                           "damage_type" : random(2)?"刺伤":"割伤",
                         ]);
                   } 
                  if( me->query_temp("juan")){ 
                  return ([  
                           "action" : CYN+action[j]["action"]+NOR,
                           "force" : action[j]["force"]+60,
                           "dodge": action[j]["dodge"]+15,
                           "damage": action[j]["damge"]+level/4,
                           "lvl" : action[j]["lvl"],
                           "parry":action[j]["parry"]+ 20,
                           "weapon" : random(2)?"剑气":"剑锋",
                           "damage_type" : random(2)?"刺伤":"割伤",
                         ]);
                   } 
                return action[j];
                }
        }
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
        if (me->query("jingli") < 40)
                return notify_fail("你的体力不够练玉女素心剑。\n");
        if(me->query("neili") < 20)
		return notify_fail("你的内力不够练玉女素心剑。\n");
        me->add("jingli", -25);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yunu-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int skill = me->query_skill("yunu-jianfa", 1)/20;
        if(random(me->query_skill("yunu-jianfa", 1)) > 60
         && me->query_temp("hebi")) {
                  victim->add_busy(random(skill/5)+2);
                  call_out("check_fight", 1, me, victim);
        }
}

void check_fight(object me,object victim)
{
        if(!victim) return;
        if( ! me 
         || ! me->is_fighting(victim)
         || me->query_skill_mapped("sword") !="yunu-jianfa"
         || ! me->query_temp("weapon")){
          if(!victim->is_busy()) victim->start_busy(1);
          return;
        }
        call_out("check_fight", 1, me, victim);
}
