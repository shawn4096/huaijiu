// jiuyang-shengong.c 九阳神功
#include <ansi.h>
inherit FORCE;
int valid_enable(string usage)
{
        return usage == "force";
}

int valid_learn(object me)
{
        if((int)me->query_skill("jiuyang-shengong", 1) < 220)
		return notify_fail("你现在只能通过读全部四册的《九阳真经》来提高九阳神功。\n");

	if ((int)me->query_skill("jiuyang-shengong", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("jiuyang-shengong", 1) >= 220 )
               return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

	return 1;
}

int practice_skill(object me)
{
        if((int)me->query_skill("jiuyang-shengong", 1) >= 220 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("jiuyang-shengong", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高九阳神功。\n");       
	}
	return notify_fail("九阳神功只能通过读全部四册的《九阳真经》来提高。\n");
}

string exert_function_file(string func)
{
        return __DIR__"jiuyang-shengong/" + func;
}

void skill_improved(object me)
{
         int i =3 +random(8);
         if( me->query_skill("jiuyang-shengong", 1) > 200
          && me->query("jiuyang/gift") + 201 < me->query_skill("jiuyang-shengong", 1)){
             if( !me->query("jiuyang/gift"))
               me->set("jiuyang/gift", me->query_skill("jiuyang-shengong", 1) -200);
             else 
               me->add("jiuyang/gift", 1);
             me->add("max_neili", i); 
             tell_object(me,HIW"\n随着九阳神功的提高，你感觉自己内力增加了"+chinese_number(i)+"点。\n"NOR);
         }
}

mapping exercise_msg(object me)
{
    return ([
      "status_msg" : HIR + me->name()+"呼翕九阳，进入人我两忘之境界" NOR,
      "start_my_msg" : "你盘膝而坐，运使九阳，气向下沉，由两肩收入脊骨，注于腰间，进入人我两忘之境界。\n",
      "start_other_msg" : me->name()+"盘膝而坐，运使九阳，气向下沉，由两肩收入脊骨，注于腰间，进入人我两忘之境界。\n",
      "halt_msg" : "$N周身微微颤动，长出口气，站了起来。\n",
      "end_my_msg" : "你呼翕九阳，抱一含元，缓缓睁开双眼，只觉得全身真气流动，体内阳气已然充旺之极。\n",
      "end_other_msg" : "只见"+me->name()+"呼翕九阳，抱一含元，缓缓睁开双眼，只觉得全身真气流动，体内阳气已然充旺之极。\n"
    ]);
}


