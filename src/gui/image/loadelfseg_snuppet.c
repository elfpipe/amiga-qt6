        	if (0) //sym->st_value)
        	{
        		pS = Elf32_TranslateAddress(sym_handle, (void *)sym->st_value);
        		lprintf(handle, 4, "SHN_UNDEF points to %p\n", pS);
        	}
        	else {
                Elf32_HandleP *res;
                sym = Elf32_GetSymbol(handle, shdr->sh_link, ELF32_R_SYM(rela->r_info));
                STRPTR name = Elf32_GetSymbolName(sym_handle, sym);
                if (!name)
                {
                    lprintf(handle, 1, "UNDEF : ERROR: Illegal name\n");
                    RETURN( ELF32_INVALID_NAME );
                }
                Elf32_Sym *dynsym = Elf32_FindDynamicSymbol(handle->Root, name, &res, handle->Root);
                lprintf(handle, 2, "UNDEF : dynsum = %p\n", dynsym);
                if (!dynsym)
                {
                    pS = 0;
                } else {
                    lprintf(handle, 1, "UNDEF : symbol name %s\n", name);
                    void *real_source = Elf32_TranslateAddress(res, (void *)dynsym->st_value);
                    // sym->st_value = (Elf32_Addr)real_source;
                    pS = real_source;
                }
                //pS = 0;
            }
