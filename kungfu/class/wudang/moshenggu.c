// moshenggu.c
// by ydh

inherit NPC;

int ask_me_1(object who);
int ask_raozhi();

void create()
{
        set_name("Ī����", ({ "mo shenggu", "mo" }));
        set("nickname", "�䵱����");
        set("long", 
                "��������������ߵ���Ī���ȡ�\n"
                "��������ᣬ����Ŀ��࣬�����ܸɡ�\n");
        set("gender", "����");
        set("age", 22);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 26);
        set("int", 30);
        set("con", 26);
        set("dex", 28);
        
        set("max_qi", 1200);
        set("max_jing", 800);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);
        set("combat_exp", 100000);
        set("score", 50000);

        set_skill("force", 80);
        set_skill("yinyun-ziqi", 60);
        set_skill("dodge", 80);
        set_skill("tiyunzong", 60);
        set_skill("cuff", 80);
        set_skill("taiji-quan", 60);
        set_skill("parry", 80);
        set_skill("sword", 80);
        set_skill("taiji-jian", 70);
        set_skill("taoism", 80);
        set_skill("literate", 80);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        prepare_skill("cuff", "taiji-quan");
        create_family("�䵱��", 2, "����");
        set("inquiry", ([
                "��ɽ" : (: ask_me_1 :),
                "��ָ�ὣ" : (: ask_raozhi :),
        ]));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
}

int ask_raozhi()
{
     object me = this_player();
     mapping myfam;
      myfam = (mapping)me->query("family");
     if (!myfam || myfam["family_name"] != "�䵱��") {    
          command("kick3 "+(string)me->query("id"));
          command("say ������ɵ��ӣ�������ʲô��");
          return 1; }
     if (me->query_temp("raozhi")) {
         command("say ���Ǹ�������ô��");
         return 1; } else {
         command("say ���Ƕ�ʦ�����ҵ�һ�����⽣�С�");
         command("say ����ѧ���ã��޷���ͨ���㻹������ȥ������ɡ�");
         me->set_temp("raozhi",1);
         return 1; }
}

int ask_me_1(object who)
{ object me;
  mapping myfam;
  me=this_player();
  myfam = (mapping)me->query("family");
 if (!myfam || myfam["family_name"] != "�䵱��") 
  { command("slap "+(string)me->query("id"));
    command("say ������ɵ��ӣ�Ҳ�������ĳ���!\n");
    return 1;
  }
 if ( (int)me->query_skill("yinyun-ziqi", 1) < 20)
   {
    command("pat "+(string)me->query("id"));
    command("say ������δ�ɣ����Ǳ���ɽ�ĺ�!\n");
    return 1;
   }
  if((int)me->query("wudang_given")<(int)me->query("age")) 
  {
    command("nod "+(string)me->query("id"));
    who->add_money("gold",(int)(me->query_skill("yinyun-ziqi", 1)/10) );
    command("give "+me->query("id")+" "+(int)(me->query_skill("yinyun-ziqi", 1))/10+" gold");
    me->set("wudang_given",(int)me->query("age"));
  }
  command("say ����ɽ��Ҫ���������壬Ҫ��Ϊ���������ұ������Ż�!\n");
  return 1;
}

