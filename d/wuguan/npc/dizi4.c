//dizi4.c ��� by river

#include <ansi.h>
inherit NPC;
int ask_wuguan();
int ask_liguan();

void create()
{
        set_name("���", ({ "sun jun","sun","jun", "man" }));
        set("title", "��������ĵ���");
        set("gender", "����");
        set("age", 21);       
        set("long", "��������ɽ���ĵ��ӣ���ò�Ͱ���һ�쵽��Ц�Ǻǵġ�\n");
        set("combat_exp", 5000);
        set("shen_type", 1);
        set("attitude", "friendly");   
        set("unique", 1);
     
        set_skill("force", 50);
        set_skill("strike", 50);
        set_skill("sword", 50);
	set_skill("shenzhao-jing",50);
        map_skill("force", "shenzhao-jing");          
 
        set("inquiry", 
                ([
                        "����ɽ" : "�����˼����ҵĶ�ʦ����",
			"���" : (:ask_liguan:),
			"���" : (:ask_wuguan:),
			"�������" :(:ask_wuguan:),
		]));
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{      
       if( !ob || environment(ob) != environment() ) return;
        if ( ob ->query("combat_exp") < 500){
        command("bow "+ob->query("id"));
        command("say �㲻���Ĵ�����"HIY HBCYN"look"CYN"��������ʲô�����㶼���Լ�����"HIY HBCYN"get"CYN"���š�\n"+
                "������Ȳ��"HIY HBCYN"i or inventory"CYN"����������������Щʲô����Ҫ��ʱ�ز��"HIY HBCYN"hp\n"+
                CYN"�������״̬��Ҫ�Ƕ��˻���˾�ȥ��Щ�Եĺȵİɡ���Ҫ����ʲô�����\n"+
                "�����ҡ�"HIY HBCYN"ask sun about ������ݣ�ask sun about ���"CYN"��\n"+
                "���ڸ���ָ��ľ����÷����Բο� "HIY HBCYN"help commands"CYN"��"NOR);
        }
}                               

int ask_wuguan()
{
      object ob;       
      ob = this_player();
      if (ob ->query("combat_exp") < 1000){
	  command("say  �������������ʦ���������֡�����ɽ�����˼�һ�ֽ����ģ�����\n"+
                  "������Ŀ�ľ����ڸ�һЩ���뽭��������һЩ������ʵ���Ļ��ᡣ����������\n"+
                  "���� "HIY HBCYN"help wuguan"CYN" �� "HIY HBCYN"help map_wuguan"CYN"��"NOR);
	  return 1;
      }
      else{
	  command("kick "+ ob->query("id"));
	  command("say �������ô��ʱ���ˣ����ڸ��𰡣��Լ���Ϥȥ�ɣ�\n");
	  return 1;
      }
}

int ask_liguan()
{
      object ob;
      ob = this_player();
      if (!ob->query("enter_wuguan")){
	 command("congra "+ob->query("id"));
	 command("say ��λ" + RANK_D->query_respect(ob)+"���Գ�ȥ���������ˣ������ն񣬿�ǧ��С�İ���������\n"+
                 "�͵�����ݣ���������Գ˳����������ɣ�����ݾ��������ˡ�");		 
	 ob->set_temp("marks/���", 1);
	 return 1;
      }
      else{
	 command("hmm "+ob->query("id"));
	 command("say ��λ" + RANK_D->query_respect(ob)+"û�й�����ͬ�⣬�ҿɲ������������뿪��ݡ�");
	 return 1;
      }
}
