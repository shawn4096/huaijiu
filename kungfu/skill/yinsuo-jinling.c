// yinsuo-jinling.c 银索金铃
// By River
#include <ansi.h>
inherit SKILL;
string  *msg = ({
"$N左手轻扬，手中$w忽地甩了出来，直扑$n的$l。无声无息，事先竟没半点朕兆",
"$N手持$w矫矢似灵蛇击向$n，再加两枚金球不断发出玎玎之声，更是扰人心魄",
"$n又听得金球中发出玎玎声响，声虽不大，却是十分怪异，入耳荡心摇魄。",
"$N身形一变，转手一挥$w，$n大惊之下，身子後仰，$w离脸数寸急掠而过",
"$N手腕微抖，$w翻将过去，自下而上，打向$n身上$l处的「合谷穴」",
"$N手中两条$w犹如水蛇般蜿蜒而出，玎玎两响，$n手腕上的「灵道穴」都被$w点中",
"$N微微一笑跨前一步，右手$w一抖，$w矫夭飞舞，好比彩凤朝阳一般抽向$n",
});

int valid_enable(string usage)
{ 
       return (usage == "whip") || (usage == "parry"); 
}

mapping query_action(object me, object weapon)
{
       return ([
           "action":msg[random(sizeof(msg))],
           "damage":(random(3)+1) * 80,
           "damage_type":random(2)?"拉伤":"卷伤",
           "dodge":random(55)-random(15),
           "force":random(200) + 200,
           "parry":random(40)- random(10),
       ]);
}

int valid_learn(object me)
{
       object weapon;
       if( (int)me->query("max_neili") < 500 )
               return notify_fail("你的内力不足，没有办法练银索金铃, 多练些内力再来吧。\n");
       if ((int)me->query_skill("yunu-xinjing", 1) < 100)
               return notify_fail("你的玉女心经内功火候太浅。\n");
       if (!objectp(weapon = me->query_temp("weapon"))
        || ( string)weapon->query("skill_type") != "whip" )
               return notify_fail("你使用的武器不对。\n");
       return 1;
}
 
int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "whip")
               return notify_fail("你使用的武器不对。\n");
       if ((int)me->query_skill("yunu-xinjing", 1) < 100)
               return notify_fail("你的玉女心经内功火候太浅。\n");
       if ((int)me->query("jingli") < 50)
               return notify_fail("你的体力不够练银索金铃。\n");
       if ((int)me->query("neili") < 30)
               return notify_fail("你的内力不够练银索金铃。\n");
       me->receive_damage("jingli", 35);
       me->add("neili", -10);
       return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
       object weap,weap1;
       weap = victim->query_temp("weapon");
       weap1 = me->query_temp("weapon");
       if( me->query_skill("yinsuo-jinling", 1) > 120
        && me->query("neili") > 700
        && victim->query_temp("weapon") 
        && random(me->query_skill("yinsuo-jinling",1)) > victim->query_skill("dodge", 1)/2
        && weap1->query("id") == "jinling suo"){
          message_vision(HIY"只见$N急速挥舞"+ weap1->name() + "，转出无数个大小圈子，以阴柔之劲缠住对方的" + weap->name() +"！\n" NOR, me ); 
          victim->start_busy(1);
          if (random(me->query_str()) > victim->query_str()/2 ){
           message_vision(HIY "\n$N气运手臂用力一拽，"+ weap->name()+ "却无法从"+weap1->name()+"的缠绕中脱开，情急之下只好放弃了手中的兵刃。\n" NOR, victim );
           weap->move(environment(me));
           victim->reset_action();
          }
          else {
           message_vision(HIY "\n$N暗运巧劲，"+ weap->name()+ "顺着方向快速旋转数下，解开了"+weap1->name()+"的缠绕。\n" NOR, victim );
           victim->add("neili", -50);
          }
          me->add("neili", -(20+random(30)));
       }
       return 1;
}

string perform_action_file(string action)
{
      return __DIR__"yinsuo-jinling/" + action;
}
