// emei sujia apprentice

void attempt_apprentice(object ob)
{
	if( (string)ob->query("class") == "bonze" )
	{	command ("say ��ֻ�ն��ҡ��׼ҵ��ӡ���");
		return;
	}
	if( (string)ob->query("gender") == "����" )
	{
		command ("say ��������ľ��ǲ��в�Ů֮�ˡ�");
		return;
	}
	command ("say �ðɣ��Ҿ������������׼ҵ��ӡ��ˡ�");
	command("recruit " + ob->query("id"));
	if( (string)ob->query("class")!="bonze" )
	{
		ob->set("title", "�������׼ҵ���");
	}
}
