inherit SKILL;
 
mapping *action = ({
([
"action":"$N跃在半空，一招「仙鹤展翅入灵山」，手中$w已化成无数棍影，令$n眼花缭乱，不知所措，连连倒退",
         "force" : 180,
         "dodge" : 20,
         "parry" : 20,
        "damage": 20,
         "lvl" : 0,
         "skill_name" : "仙鹤展翅入灵山",
         "damage_type":"挫伤"
]),
([
"action":"$N挺$w将$n的招式架住，顺势一招「玉马衔环拜仙宫」，$w上下左右飞快搅动，身随棍走，向$n压了下来",
         "force" : 200,
         "dodge" : 10,
         "parry" : 15,
        "damage": 100,
         "lvl" : 30,
         "skill_name" : "玉马衔环拜仙宫",
         "damage_type":"挫伤"
]),
([
"action":"$N一招「鸣鹿踏蹄觅仙草」，屈膝俯身，手中$w连点$n下盘，却未等招数用老，猛的一提，向$n的胸腹间戳去",
         "force" : 220,
         "dodge" : 15,
         "parry" : 20,
        "damage": 40,
         "lvl" : 60,
         "skill_name" : "鸣鹿踏蹄觅仙草",
         "damage_type":"挫伤"
]),
([
"action":"$N突然滚到在地，$n错愕间，一招「金鲤跃水潜天池」，竟从$n的裆下窜过，更不回头，$w反手扫向$n的$l",
         "force" : 240,
         "dodge" : 20,
         "parry" : 25,
        "damage": 60,
         "lvl" : 80,
         "skill_name" : "金鲤跃水潜天池",
         "damage_type":"挫伤"
]),
([
"action":"$N一招「灵猿献果赴蓬莱」，身形如电，绕着$n飞快奔跑，手中$w一招快似一招，刹那间向$n连打出十六棍",
         "force" : 280,
         "dodge" : 30,
         "parry" : 30,
        "damage": 80,
         "lvl" : 100,
         "skill_name" : "灵猿献果赴蓬莱",
         "damage_type":"挫伤"
]),
([
"action":"$N大踏步上前，劲贯双臂，手中$w大开大阖，呼呼风声中一招「飞鹰盘旋扫乾坤」扫向$n的腰间",
         "force" : 260,
         "dodge" : 30,
         "parry" : 40,
        "damage": 100,
         "lvl" : 120,
         "skill_name" : "飞鹰盘旋扫乾坤",
         "damage_type":"挫伤"
]),
([
"action":"$N大喝一声，一招「天龙出水腾宇宙」，$w脱手飞出，夹着劲风射向$n的前心，随即抢到$n的身后，伸手又把$w抄在手中",
         "force" : 300,
         "dodge" : 20,
         "parry" : 30,
        "damage": 80,
         "lvl" : 130,
         "skill_name" : "天龙出水腾宇宙",
         "damage_type":"挫伤"
]),
([
"action":"$N双目圆睁，口中默诵真言，一招「白象卷云憾天柱」，$w似有千斤，缓缓举起，又缓缓向$n的当头砸落",
         "force" : 350,
         "dodge" : 20,
         "parry" : 30,
        "damage": 100,
         "lvl" : 150,
         "skill_name" : "白象卷云憾天柱",
         "damage_type":"挫伤"
]),
});
 
int valid_enable(string usage) { return  (usage == "club") || (usage =="parry"); }
 
int valid_learn(object me)
{
           mapping fam  = me->query("family");
         if (fam["family_name"] != "少林派" )
         	return notify_fail("韦陀杵只能从少林派学到。\n");
	if( me->query("passdu"))
		return notify_fail("你已是三长老的及门高弟，如何能修习这种大误禅宗修为的刚猛武功？\n" );
         if ((int)me->query("max_neili") < 1500)
                return notify_fail("你的内力不够。\n");
         if ((int)me->query_skill("yijin-jing", 1) < 160)
                return notify_fail("你的易筋经内功火候太浅。\n");
         if((int)me->query_skill("zui-gun",1) <=120)
      		return notify_fail("你的醉棍火候不足，难以领悟韦陀杵。\n");
         if ((int)me->query_skill("ranmu-daofa",1) || (int)me->query_skill("riyue-bian",1))
                return notify_fail("你如果有达摩老祖的修为，方可同时学习少林三绝技。\n"); 
         return 1;
}
 
string perform_action_file(string action)
{
        return __DIR__"weituo-chu/" + action;
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
         int i, level, lvl;
         object target;
         mapping pre;
         string *skill, a, b;
         
         level   = (int) me->query_skill("weituo-chu",1);
         lvl = (int)me->query_skill("longzhua-gong", 1);
         
         
         if ( level >= 200 && lvl >= 200 && random(level) > lvl / 2
         && objectp(target = me->select_opponent())
         && objectp(weapon = me->query_temp("weapon"))
         && me->query_skill_mapped("claw") == "longzhua-gong" 
         && me->query_skill_prepared("claw") == "longzhua-gong" 
         && me->query("neili") > 300 && me->query("jingli") > 100 ) {
         	pre = me->query_skill_prepare();
        	skill = keys(pre);     
        	for (i=0; i<sizeof(skill); i++){
                	if(skill[i]=="claw") continue; 
                	a = skill[i];
                	b = pre[skill[i]];
                	me->prepare_skill(skill[i]);
        	}
        	
                weapon->unequip();
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
                weapon->wield();
                me->prepare_skill(a,b);
                me->add("neili", -25);
                me->add("jingli", -10);
         }
        


         for(i = sizeof(action); i > 0; i--)
                 if(level >= action[i-1]["lvl"])
                         return action[NewRandom(i, 20, level/5)];
}
 
int practice_skill(object me)
{
         object weapon;
         if((int)me->query_skill("zui-gun",1) <=120)
      		return notify_fail("你的醉棍火候不足，难以领悟韦陀杵。\n");
      		
         if ((int)me->query_skill("ranmu-daofa",1) >1 || (int)me->query_skill("riyue-bian",1)>1)
                return notify_fail("你如果有达摩老祖的修为，方可同时学习少林三绝技。\n"); 
         if (!objectp(weapon = me->query_temp("weapon"))
                  || (string)weapon->query("skill_type") != "club")
                return notify_fail("你使用的武器不对。\n");
         if ((int)me->query("jingli") < 70)
                return notify_fail("你的体力不够练韦陀棍。\n");
         if ((int)me->query("neili") < 40)
                return notify_fail("你的内力不够练韦陀棍。\n");
                
 me->receive_damage("jingli", 30);           
         if((int)me->query_skill("weituo-chu",1)> 200)
 me->add("neili",-10);

         return 1;
}
