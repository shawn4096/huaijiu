// ��־��

inherit F_MASTER;
inherit NPC;
void create()
{
        set_name("��־��", ({ "zhong zhiling","zhong" }));
	set("long", "����ʮ������ͣ��������̰���������ʹ��\n");
      set("gender", "����");
	set("title", "�����̰���������ʹ");	
      set("age", 42);       
	set("str", 20);
      set("int", 22);
      set("con", 22);
      set("dex", 22);
      set("per", 15);
      set("combat_exp", 350000);
      set("shen", -50000);
      set("attitude", "peaceful");
	set("max_qi",1500);
      set("max_jing",1500);
      set("neili",1500);
      set("max_neili",1500);
      set("jingli",1200);
      set("eff_jingli",1200);
	set("jiali",35);
	set("score", 20000);

      //set_skill("unarmed", 150);
	set_skill("force", 80);
	set_skill("dodge", 80);
       //set_skill("move", 180);
      set_skill("parry",80);
	set_skill("strike",80);
      //set_skill("throwing",80);
      set_skill("whip",80);
      set_skill("huagu-mianzhang", 80);
      set_skill("youlong-shenfa",80);
      set_skill("dulong-dafa",80);
      //set_skill("hanshasheying",150);
      set_skill("lingshe-bianfa",80);
      
	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
	//map_skill("move", "youlong-shengfa");
       map_skill("strike", "huagu-mianzhang");
      //map_skill("unarmed","huagu-mianzhang");
      map_skill("parry","huagu-mianzhang");
      map_skill("whip", "lingshe-bianfa");
      //map_skill("throwing","hanshasheying");

      prepare_skill("strike", "huagu-mianzhang");

      create_family("������",2, "����ʹ");
      setup();
      carry_object("/d/sld/npc/obj/wcp")->wear();        
}

void attempt_apprentice(object ob)
{
       mapping myfam;

       myfam = (mapping)ob->query("family");
 	if(!myfam || myfam["family_name"] != "������")
           command("say ��Ǳ��̵��ӣ�������ȥ�����ʹ��̰�.");
       else if(ob->query("shen",1) > -5000)
           command("say �㻹�����ĺ���������ȥ��ɱ�����׵����˰�");
       else if(ob->query_skill("dulong-dafa",1)<40 || ob->query_skill("huagu-mianzhang",1)<40)
                   command("shake "+ob->query("id"));
       else
            {
           command("say �ðɣ��Ҿ����������ҵĵ��ӡ�");
	    command("recruit " + ob->query("id"));
       }
	return;	
}

int recognize_apprentice(object ob)
{
    mapping myfam;
    object hw;

    myfam = (mapping)ob->query("family");
if(!myfam || (myfam["family_name"] != "������")) return 0;
     if(!ob->is_apprentice_of(this_object())) return 0;
    if(myfam && (myfam["family_name"] == "������")&&(ob->query("shen",1) >0))
    {
    	command("say �ߣ��㾹Ȼ�ҺͰ׵����˸���һ���ǲ��ǲ�����ˣ���ȥ���ݺú÷�ʡ��ʡ�ɣ�");
	if(!objectp(hw=find_object("/d/sld/npc/obj/heiwu")))
		hw=load_object("/d/sld/npc/obj/heiwu");
	ob->set("in_heiwu",time());
	ob->move(hw);        
        return 0;
    }
    return 1;
}
