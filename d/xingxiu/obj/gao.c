inherit ITEM;

#include <ansi.h>


int do_chang(string);

void create() 
  {
   set_name(HIY "�ĳ��" NOR,({"gao"}));
   set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
   set("long","һ���������̵�"+this_object()->query("name")+"��������(chang)ζ����\n");
   set("unit","��");
	set("no_drop", 1);
	set("no_get", 1);
	}
   setup();
  }

void init()
{
  add_action("do_chang", "chang");
}

int do_chang(string arg)
  {
  	
   object me=this_object();
   object who=this_player();
   mapping fam=who->query("family");
          if( who->is_busy()) return notify_fail("����æ���ء�\n");
   if( !this_object()->id(arg) ) return notify_fail("���볢ɶ��\n");
   message_vision("$N����"+me->query("name")+"����һ�ڵĳ�����ȥ��\n", who);
   if (!fam || fam["family_name"] !="������"){
                return notify_fail("�㲻�����޵��ӣ�������"+me->name()+"���ж��ġ�\n");
        }
   if ( me->query("prices")<= 0 || me->query("xx/owner")!=who)  message_vision("��ʲô��ζҲû��������\n", who);
   else if (who->query("combat_exp") > 2000000 || who->query_skill("huagong-dafa", 1) < 10)
     {
      message_vision("$Nֻ�е�һ����ģ�������ת��\n", who);
      who->unconcious();
     }
   else 
     {
      message_vision("$N������������ǿ����û�³�����\n", who);
      //who->improve_skill("force", me->query("prices"));
      tell_object(who,"��ֻ�е�����������ʮ��С���������Ҵ̣���ʹ����������"
         +"�Ž���ҩ��ҩ����ȫ���⡣\n");
      who->add("combat_exp",me->query("prices"));
        who->add("potential",me->query("prices")/4);
         who->add("xx_job4",4);
        if(who->query("potential") > who->query("max_pot")) 
                who->set("potential",who->query("max_pot"));
      tell_object(who, YEL "��ľ����Ǳ�ܸ�������"
         +chinese_number(me->query("prices"))+"�㣡\n" NOR);
      log_file( "job/xx_job4",sprintf("%s %s(%s)��%d������������õ�Ǳ�ܺ;��飺%d��\n",
                ctime(time())[4..19],who->name(),who->query("id"),who->query("xx_job4"),me->query("prices")) );
     } 
   destruct(me);
   return 1;
  }

