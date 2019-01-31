// 兵器铺
// bqp.c -- Oct 25,97
// Looklove 2001/2/27

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
           set("short",HIR"兵器铺"NOR);
           set("long",@long
这是一间灯火通明的兵器铺，里边放着一排排的兵器架，上面放满了兵
器。一位老师傅和一个中年男子正在打造着一件希奇古怪的兵器，你从来没
有见过这个兵器，不禁想上去与他们搭个话。墙上有一个大招牌(sign)。
long ); 
        set("objects",([
        "/clone/npc/tiejiang_test" : 1,
        "/d/city/npc/tiejiang" : 1,
                ]));
                  
        set("exits",([
                "west" : __DIR__"datiepu",
                ]));
        
        set("item_desc",([
                "sign" : 
                "
                 本店承定各种兵器。

                 用     ding <weapon_type> <color> <weapon_name>  来订造.
                        例如 : ding sword $HIY$ 碧血剑
                                 
                Notes: weapon_type   blade,sword,club,staff,feibiao,hook;
                        color         $HIG$ $HIR$ etc, see help nick
                             for the full list of supported color;
                        weapon_name   你所要打造的兵器的中文名字

                        ***   对于不雅观的兵器,巫师将予以没收!   ***\n"
           ]));
        set("coor/x",130);
        set("coor/y",-20);
        set("coor/z",0);
        setup();
}

void init()
 {
         add_action("do_canwu", "cuilian");
 }

int do_canwu(string arg)
 {
     object me = this_player();
     object wpn, thing;

     if( !arg )
           return notify_fail("格式： cuilian <你身上要淬炼的武器>\n");
     
     if( !objectp(wpn = present(arg, me)) )
           return notify_fail("你身上没有这样东西。\n");

     if( wpn->query("equipped") )
           return notify_fail("要淬炼，你先放下武器吧。\n");

     if( !wpn->query("imbued") )
           return notify_fail("只有打造武器才能被淬炼。\n");

     if (me->is_busy() || me->is_fighting() || me->query_temp("con_weapon") )
           return notify_fail("你正忙着呢。\n");

     if (me->query_temp("canwu_now") )
           return notify_fail("你正忙着呢。\n");
       
     if (query_temp("canwu") )
           return notify_fail("有人正在淬炼呢，你等一会把。\n");

     if ( me->query("balance") < 5000000 )
         
           return notify_fail("每次淬炼需要支付500两黄金，你的存款不够。\n");

     if ( wpn->query("weapon_mp/saved",1)!= me->query("id") )   
           return notify_fail("这并不是你自己的私人武器，你何苦花大力气去淬制养护呢。\n");

     if ( wpn->query("weapon_mp/weapon_prop/damage",1) >= 300)

           return notify_fail("你手中乃是当世数一数二的神兵，根本不需要再加淬制了。\n");
     thing = present("yun shi", me);
     if (!thing || !thing->query("weapon_pro") ) 
	      return notify_fail("你没有天外陨石，如何能够淬炼兵器!\n");

       message_vision( HIW"$N将随身携带的兵器和天外陨石在火炉旁准备好。\n"NOR,me);
       message_vision( HIW"$N在韦兰铁匠的指导下开始在炉火上淬炼起来。 \n"NOR, me);
  
       me->start_busy(100);
       me->set_temp("canwu_now",1); 
       set_temp("canwu",1);
       me->add("balance",-5000000);
       destruct(thing);
       call_out("thinking",5, me, wpn);
       return 1;

 }

int thinking(object me,object wpn)
{
  int temp, limit, i;
  if(!me) return 0;
  i = wpn->query("imbued");
  limit = 150;
  switch(i){
		case 5: 
		case 4: limit = 300; break;
		case 3: limit = 250; break;
		case 2: limit = 200; break;
		default: break;
	}
	
  if(me->query_temp("con_weapon")<(3+random(3)))
       {  me->add_temp("con_weapon",1);
          tell_object(me,HIY"\n你按照韦兰铁匠的指导，挥动铁锤试图将天外陨石融合到武器之中...\n"NOR);  
	  message_vision( HIC"$N默运玄功，"+wpn->query("name")+""HIC"慢慢地泛出一道奇异的光辉...\n"NOR, me);
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me, wpn);
	}

 else { 
         me->delete_temp("con_weapon");
         me->start_busy(1);     
         message_vision(HIC"\n$N手中"+wpn->query("name")+""HIR"忽做龙吟，似乎增加了不少威力！\n"NOR,me); 

         tell_object(me,HIR"\n你对"+wpn->name()+""HIR"成功的进行了一次淬炼！\n"NOR);
         
         temp=10+random(10);         
         if(wpn->query("weapon_prop/damage",1) >100) 
                 temp=5+random(5);
         if(wpn->query("weapon_prop/damage",1) >200) 
                 temp=2+random(3);

         wpn->add("weapon_prop/damage",temp);
         me->add("user_weapon/weapon_prop/damage",temp);

         if(wpn->query("weapon_prop/damage",1) > limit)  
                 wpn->set("weapon_prop/damage",limit);
         if(me->query("user_weapon/weapon_prop/damage",1) > limit) { 
                 me->set("user_weapon/weapon_prop/damage",limit);
                 tell_object(me,HIR"\n你发觉"+wpn->name()+""HIR"的自身潜力已发挥到极致！\n"NOR);
         }

         me->delete_temp("canwu_now");
         delete_temp("canwu");   
       }
}