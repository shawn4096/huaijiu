//dizi7.c ��̹ by river

inherit NPC;

#include <ansi.h>
void create()
{
        set_name("��̹", ({ "feng tan", "feng", "tan"}));
	set("title","��������ߵ���");
        set("long", "��������ɽ���ߵ��ӣ���Ĭ���ԣ�һ��������������ӡ�\n");
        set("gender", "����");
        set("age", 22); 
        set("combat_exp", 5000);
        set("shen_type", 1);
        set("unique", 1);

        set_skill("force", 35);
        set_skill("strike", 35);
        set_skill("sword", 35);
	set_skill("shenzhao-jing",35);
        map_skill("force", "shenzhao-jing");          

        set("startroom","/d/wuguan/dayuan");

        set("chat_chance", 3);
        set("chat_msg", ({            
                 (: random_move :)
        }) );
       
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int get_object(object who)
{
        if(userp(who))
        return 1;
        return 0;
}

void greeting(object ob)
{
      object *inv;
      object *obj,where;

	if (!ob) return;
      inv = deep_inventory(ob);
      where = environment(ob);
      if( !ob || environment(ob) != environment() ) return;        
      if ( ob->query("combat_exp") < 3500 ) return;
      if (wizardp(ob)) return;  
      command("disapp "+ ob->query("id"));
      command("say ��λ" + RANK_D->query_respect(ob)+ "�����Ѿ��ܵ�����Ľ�����ȥ����һ���ˣ���ô������\n"+
              "�����͵������ݲ�ϣ���������ڴ˵��ˡ�\n");
      message_vision(HIR"ֻ����һ�����˰���$N��һ������������ˡ�\n"NOR, ob);
      ob->delete("enter_wuguan");
      obj = filter_array(inv,(:get_object:));
      if( sizeof(obj))
       obj->move(where);
      ob->unconcious();
      ob->move("/d/xiangyang/damen");
}
