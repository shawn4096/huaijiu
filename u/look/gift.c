#include <ansi.h>

inherit ITEM;

int launching(object me);
void init()
{
    if(wizardp(this_player()))
       add_action("do_launch", "send");
}

void create()
{
       set_name(GRN"ʥˮ"NOR, ({"holly water", "water"}));
       if (clonep())
               set_default_object(__FILE__);
       else {
               set("value", 1000);
               set("unit", "��");
               set("no_get", 0);
               set("no_drop", 0);
       }
}

int do_launch()
{
       object *dest;
       int i, j;
       
       j = 0;
       dest = users();
       i = sizeof(dest);
       while(i--)
        if(!dest[i]->query("gift/����") && dest[i]->query("registered")
           && dest[i]->query("age") && (int)dest[i]->query("combat_exp")>1000){
                 j = 1;
	         message_vision(HIY "���ڸ�"+dest[i]->query("name")+"�������\n"NOR,this_object());  
                 launching(dest[i]);
                 break;
         }
             
       if(j < 1){
         message_vision(HIY "���ˣ��Ѿ������ˡ�\n"NOR,this_object());  
         destruct(this_object());                
         return 1;
         }
       return 1;
}

int launching(object me)
{
          tell_object(me, GRN "һ����" BLINK "����ף�ر��齣��վ��ʽ��վ��" GRN "���������ϵ���һ�����������������Ľ��ϣ�\n" NOR);
          new("/u/bbb/bag")->move(me);
          EMOTE_D->do_emote(me,"pain"); 
          me->set("gift/�·�վ", 1);
          remove_call_out("do_launch");
          call_out("do_launch", 8);
          return 1;
}
