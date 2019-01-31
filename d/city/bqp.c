// ������
// bqp.c -- Oct 25,97
// Looklove 2001/2/27

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
           set("short",HIR"������"NOR);
           set("long",@long
����һ��ƻ�ͨ���ı����̣���߷���һ���ŵı����ܣ���������˱�
����һλ��ʦ����һ�������������ڴ�����һ��ϣ��Źֵı����������û
�м��������������������ȥ�����Ǵ������ǽ����һ��������(sign)��
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
                 ����ж����ֱ�����

                 ��     ding <weapon_type> <color> <weapon_name>  ������.
                        ���� : ding sword $HIY$ ��Ѫ��
                                 
                Notes: weapon_type   blade,sword,club,staff,feibiao,hook;
                        color         $HIG$ $HIR$ etc, see help nick
                             for the full list of supported color;
                        weapon_name   ����Ҫ����ı�������������

                        ***   ���ڲ��Ź۵ı���,��ʦ������û��!   ***\n"
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
           return notify_fail("��ʽ�� cuilian <������Ҫ����������>\n");
     
     if( !objectp(wpn = present(arg, me)) )
           return notify_fail("������û������������\n");

     if( wpn->query("equipped") )
           return notify_fail("Ҫ���������ȷ��������ɡ�\n");

     if( !wpn->query("imbued") )
           return notify_fail("ֻ�д����������ܱ�������\n");

     if (me->is_busy() || me->is_fighting() || me->query_temp("con_weapon") )
           return notify_fail("����æ���ء�\n");

     if (me->query_temp("canwu_now") )
           return notify_fail("����æ���ء�\n");
       
     if (query_temp("canwu") )
           return notify_fail("�������ڴ����أ����һ��ѡ�\n");

     if ( me->query("balance") < 5000000 )
         
           return notify_fail("ÿ�δ�����Ҫ֧��500���ƽ���Ĵ�����\n");

     if ( wpn->query("weapon_mp/saved",1)!= me->query("id") )   
           return notify_fail("�Ⲣ�������Լ���˽����������ο໨������ȥ���������ء�\n");

     if ( wpn->query("weapon_mp/weapon_prop/damage",1) >= 300)

           return notify_fail("���������ǵ�����һ�������������������Ҫ�ټӴ����ˡ�\n");
     thing = present("yun shi", me);
     if (!thing || !thing->query("weapon_pro") ) 
	      return notify_fail("��û��������ʯ������ܹ���������!\n");

       message_vision( HIW"$N������Я���ı�����������ʯ�ڻ�¯��׼���á�\n"NOR,me);
       message_vision( HIW"$N��Τ��������ָ���¿�ʼ��¯���ϴ��������� \n"NOR, me);
  
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
          tell_object(me,HIY"\n�㰴��Τ��������ָ�����Ӷ�������ͼ��������ʯ�ںϵ�����֮��...\n"NOR);  
	  message_vision( HIC"$NĬ��������"+wpn->query("name")+""HIC"�����ط���һ������Ĺ��...\n"NOR, me);
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me, wpn);
	}

 else { 
         me->delete_temp("con_weapon");
         me->start_busy(1);     
         message_vision(HIC"\n$N����"+wpn->query("name")+""HIR"�����������ƺ������˲���������\n"NOR,me); 

         tell_object(me,HIR"\n���"+wpn->name()+""HIR"�ɹ��Ľ�����һ�δ�����\n"NOR);
         
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
                 tell_object(me,HIR"\n�㷢��"+wpn->name()+""HIR"������Ǳ���ѷ��ӵ����£�\n"NOR);
         }

         me->delete_temp("canwu_now");
         delete_temp("canwu");   
       }
}